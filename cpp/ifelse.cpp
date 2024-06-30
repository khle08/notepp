#include <sys/time.h>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <iomanip> 
#include <unistd.h>    // for "usleep"
#include <iostream>

#include <thread>

#define print(x) std::cout << x << std::endl

typedef std::chrono::high_resolution_clock::time_point chtime;


int main()
{
    int a = 0;

    while (true) {
        if (a == 0) {
            print("a = 0");
            a += 1;
        } else if (a == 1) {
            print("a = 1");  // this will be skipped permanently
        }
        a += 1;

        usleep(1 * 1000 * 1000);
    }

    return 0;
}

