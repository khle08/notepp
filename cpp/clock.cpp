
#include <ctime>
#include <chrono>
#include <iomanip> 
#include <unistd.h>    // for "usleep"
#include <iostream>

#include <thread>


#define print(x) std::cout << x << std::endl


int main()
{
    // Method No.1  <-- Do not know why ... it is not accurate !!
    clock_t start = clock();

    // do something...
    usleep(0.001 * 1000 * 1000);    // 1s

    clock_t end   = clock();

    print("花费了" << (double)(end - start) / CLOCKS_PER_SEC << "秒");


    // Method No.2  <-- Use this instead of the 1st method
    // ref: https://www.jianshu.com/p/0ccbf45491de
    // where "auto" is "std::chrono::time_point"

    // auto t1 = std::chrono::system_clock::now();
    auto t1 = std::chrono::high_resolution_clock::now();

    // do something...
    usleep(0.314 * 1000 * 1000);    // 0.314 s
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::chrono::nanoseconds            duration<64bits+, std::nano>
    // std::chrono::microseconds           duration<55bits+, std::micro>
    // std::chrono::milliseconds           duration<45bits+, std::milli>
    // std::chrono::seconds                duration<35bits+>
    // std::chrono::minutes                duration<29bits+, std::ratio<60>>
    // std::chrono::hours                  duration<23bits+, std::ratio<3600>>
    // std::chrono::days            c++20  duration<25bits+, std::ratio<86400>>
    // std::chrono::weeks           c++20  duration<22bits+, std::ratio<604800>>
    // std::chrono::months          c++20  duration<20bits+, std::ratio<2629746>>
    // std::chrono::years           c++20  duration<17bits+, std::ratio<31556952>>

    // auto t2 = std::chrono::system_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = t2 - t1;
    print("use " << diff.count() << " s\n");

    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    print("use " << diff.count() << " s\n");

    std::chrono::duration<double, std::nano> fp_nanos = t2 - t1;
    print("use " << diff.count() << " s\n");

    print("======= get time stamp ======");
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    print(std::put_time(&tm, "%Y/%m/%d %H:%M:%S"));

    return 0;
}

