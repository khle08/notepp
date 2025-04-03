#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

// 前置声明
struct ThreadPool;
void* thread_pool_worker(void* arg);

// 线程池任务结构体
typedef struct {
    void (*task_func)(void*);   // 任务函数指针
    void* arg;                  // 任务参数
} ThreadPoolTask;

// 线程池结构体
typedef struct ThreadPool {
    pthread_t* threads;         // 线程数组
    ThreadPoolTask* queue;      // 任务队列
    int max_threads;            // 最大线程数
    int queue_size;             // 任务队列大小
    int queue_front;            // 队列头部
    int queue_rear;             // 队列尾部
    int task_count;             // 当前任务数
    pthread_mutex_t mutex;      // 互斥锁
    pthread_cond_t not_empty;   // 条件变量：队列非空
    pthread_cond_t not_full;    // 条件变量：队列不满
    int shutdown;               // 关闭标志
} ThreadPool;

// 初始化线程池
ThreadPool* thread_pool_init(int max_threads, int queue_size) {
    // 使用 static_cast 进行显式类型转换
    ThreadPool* pool = static_cast<ThreadPool*>(malloc(sizeof(ThreadPool)));
    if (!pool) return NULL;

    pool->max_threads = max_threads;
    pool->queue_size = queue_size;
    pool->queue_front = 0;
    pool->queue_rear = 0;
    pool->task_count = 0;
    pool->shutdown = 0;

    // 使用 static_cast 进行显式类型转换
    pool->threads = static_cast<pthread_t*>(malloc(sizeof(pthread_t) * max_threads));
    pool->queue = static_cast<ThreadPoolTask*>(malloc(sizeof(ThreadPoolTask) * queue_size));
    if (!pool->threads || !pool->queue) {
        free(pool->threads);
        free(pool->queue);
        free(pool);
        return NULL;
    }

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->not_empty, NULL);
    pthread_cond_init(&pool->not_full, NULL);

    for (int i = 0; i < max_threads; i++) {
        pthread_create(&pool->threads[i], NULL, thread_pool_worker, pool);
        pthread_detach(pool->threads[i]);
    }
    return pool;
}

// 线程工作函数
void* thread_pool_worker(void* arg) {
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while (1) {
        pthread_mutex_lock(&pool->mutex);
        while (pool->task_count == 0 && !pool->shutdown) {
            pthread_cond_wait(&pool->not_empty, &pool->mutex);
        }
        if (pool->shutdown) {
            pthread_mutex_unlock(&pool->mutex);
            return NULL;
        }

        ThreadPoolTask task = pool->queue[pool->queue_front];
        pool->queue_front = (pool->queue_front + 1) % pool->queue_size;
        pool->task_count--;
        pthread_cond_signal(&pool->not_full);
        pthread_mutex_unlock(&pool->mutex);

        task.task_func(task.arg);
        free(task.arg); // 释放任务参数
    }
    return NULL;
}

// 添加任务到线程池
int thread_pool_add_task(ThreadPool* pool, void (*task_func)(void*), void* arg) {
    pthread_mutex_lock(&pool->mutex);
    while (pool->task_count == pool->queue_size && !pool->shutdown) {
        pthread_cond_wait(&pool->not_full, &pool->mutex);
    }
    if (pool->shutdown) {
        pthread_mutex_unlock(&pool->mutex);
        return -1;
    }

    pool->queue[pool->queue_rear].task_func = task_func;
    pool->queue[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1) % pool->queue_size;
    pool->task_count++;
    pthread_cond_signal(&pool->not_empty);
    pthread_mutex_unlock(&pool->mutex);
    return 0;
}

// 销毁线程池
void thread_pool_destroy(ThreadPool* pool) {
    if (!pool) return;

    pthread_mutex_lock(&pool->mutex);
    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->not_empty);
    pthread_mutex_unlock(&pool->mutex);

    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->not_empty);
    pthread_cond_destroy(&pool->not_full);

    free(pool->threads);
    free(pool->queue);
    free(pool);
}

// 处理客户端请求的任务函数
void handle_client(void* arg) {
    int client_fd = *static_cast<int*>(arg);
    char buffer[1024];
    int n = read(client_fd, buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received: %s\n", buffer);
        write(client_fd, "ACK\n", 4); // 简单响应
    }
    close(client_fd);
}

// 主函数：服务器端
int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 创建线程池
    ThreadPool* pool = thread_pool_init(4, 10); // 4个线程，队列大小10
    if (!pool) {
        perror("Thread pool init failed");
        return 1;
    }

    // 创建服务器套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }

    printf("Server listening on port 8080...\n");

    // 主循环接受客户端连接
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        // 使用 static_cast 进行显式类型转换
        int* client_fd_ptr = static_cast<int*>(malloc(sizeof(int)));
        if (!client_fd_ptr) {
            close(client_fd);
            continue;
        }
        *client_fd_ptr = client_fd;

        if (thread_pool_add_task(pool, handle_client, client_fd_ptr) < 0) {
            free(client_fd_ptr);
            close(client_fd);
        }
    }

    close(server_fd);
    thread_pool_destroy(pool);
    return 0;
}