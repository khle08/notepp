#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <future>
#include <atomic>
#include <functional>
#include <condition_variable>


class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    template <typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type> {
        using returnType = typename std::result_of<Func(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

        std::future<returnType> result = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) throw std::runtime_error("ThreadPool is stopped!");
            tasks.emplace([task]() { (*task)(); });
        }
        condition.notify_one();
        return result;
    }

private:
    std::vector<std::thread> workers;            // 工作线程
    std::queue<std::function<void()>> tasks;     // 任务队列

    std::mutex queueMutex;                       // 任务队列锁
    std::condition_variable condition;           // 条件变量
    std::atomic<bool> stop;                      // 停止线程池标志
};


#endif  // _THREADPOOL_H_
