
/***
 * this project helps to demonstrate the performance of the <chrono_timer> in different threads
 * and the topological structure of the main_therad, t1 and t2 thread is similar with the ADAS program.
 */

#include <iostream>
#include <chrono>
// example for thread::join
#include <thread>         // std::thread, std::this_thread::sleep_for

std::chrono::duration<double> sum;

void draw(std::chrono::time_point<std::chrono::system_clock> t1){
    std::this_thread::sleep_for (std::chrono::microseconds (500000));
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - t1;
    std::cout << "222222222 Time to fill and iterate a vector of " << " ints : " << diff.count() << " s\n";
}


[[noreturn]] void pause_thread1()
{
    while(1){
        auto start = std::chrono::system_clock::now();
        std::this_thread::sleep_for (std::chrono::microseconds (1000000));
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end - start;
        sum += diff;
        std::cout << "111111111111 Time to fill and iterate a vector of " << " ints : " << sum.count() << " s\n";

//        std::vector<int> m;
//        m.push_back(1);
//        m.push_back(2);
//        std::cout<<m<<std::endl;
//        std::cout<<~m<<std::endl;
    }
}

[[noreturn]] void pause_thread2(){
    while(1){
        auto start = std::chrono::system_clock::now();
        std::this_thread::sleep_for (std::chrono::microseconds (5000000));
        draw(start);
//        auto end = std::chrono::system_clock::now();
//        std::chrono::duration<double> diff = end - start;
//        std::cout << "222222222 Time to fill and iterate a vector of " << " ints : " << diff.count() << " s\n";
    }
}

int main(){
    /***
     * here, two threads are defined and each thread function has a timer statement to timing the elapsed time independently
     */
    std::cout << "Spawning 3 threads...\n";
    std::thread t1 (pause_thread1);
    std::thread t2 (pause_thread2);
    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    t1.join();
    t2.join();
    std::cout << "All threads joined!\n";
}
