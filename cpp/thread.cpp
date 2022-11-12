#include <map>
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"

// #include <chrono>
// using namespace std::chrono_literals;  // for "ms"
using namespace std::literals::chrono_literals;

#define print(x) std::cout << x << std::endl


void func1() {
    for (int i = 0; i < 10; i++) {
        print("f1::" << i << "\n");
        std::this_thread::sleep_for(0.9s);
    }
}


void func2(std::string p) {
    for (int i = 0; i < 10; i++) {
        print(p << "::" << i << "\n");
        std::this_thread::sleep_for(0.9s);
    }
}


void refresh(std::map<std::string, int> forecast)
{
    while (true) {
        for (auto &item: forecast) {
            item.second++;
            print(item.first << " -> " << item.second);
        }

        // usleep(1 * 1000 * 1000);
        std::this_thread::sleep_for(1s);
    }
    return;
}


int main()
{
    std::map<std::string, int> forecast = {
        {"Tokyo", 20},
        {"Taipei", 25},
        {"Berlin", 15}
    };

    // Start running worker1 here ...
    std::thread worker1(func1);
    std::thread worker2(func2, " -> f2 ");
    usleep(1 * 1000 * 1000);    // 1s

    std::thread bgWorker(refresh, forecast);

    // ... but here worker1 and worker2 should wait for one loop execution of
    // "bgWorker" and the next loop of worker1 and worker2 can keep running
    bgWorker.join();
    worker1.join();
    worker2.join();

    // Run the thread until the thread is "detach"ed.
    // worker1.detach();
    // worker2.detach();
    // bgWorker.detach();

    // system("pause>nul");
    return 0;
}

