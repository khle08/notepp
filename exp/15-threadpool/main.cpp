
#include <iostream>
#include "threadPool.h"


void simulateWork(int input) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 模拟计算延迟
    std::cout << "Processed input: " << input 
              << " on thread " << std::this_thread::get_id() << std::endl;
}


int main() {
    ThreadPool pool(10); // 创建 4 个线程的线程池

    std::vector<std::future<void>> results;
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(pool.enqueue(simulateWork, i));
    }

    for (auto& result : results) {
        result.get(); // 等待任务完成
    }

    return 0;
}
