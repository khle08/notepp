#include <map>
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"

#include <chrono>
using namespace std::chrono_literals;  // for "ms"

#define print(x) std::cout << x << std::endl


void func1() {
    for (int i = 0; i < 10; i++) 
        print("+ ");

    return;
}


void func2(std::string p) {
    for (int i = 0; i < 10; i++)
        print(p);

    return;
}


void refresh(std::map<std::string, int> forecast)
{
    while (true) {
        for (auto &item: forecast) {
            item.second++;
            print(item.first << " -> " << item.second);
        }
        usleep(1 * 1000 * 1000);
    }
    return;
}


int main()
{
    std::thread worker1(func1);
    std::thread worker2(func2, "= ");
    usleep(2 * 1000 * 1000);

    std::map<std::string, int> forecast = {
        {"Tokyo", 20},
        {"Taipei", 25},
        {"Berlin", 15}
    };

    std::thread bgWorker(refresh, forecast);

    worker1.join();
    worker2.join();
    bgWorker.join();

    // Run the thread until the thread is "detach"ed.
    // worker1.detach();
    // worker2.detach();
    // bgWorker.detach();

    // system("pause>nul");
    return 0;
}

