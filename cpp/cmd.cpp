
// link: https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"
// #include <windows.h>

#define print(x) std::cout << x << std::endl


std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
};


int main() {
    // Purely run the CMD without knowing the output logs
    // int s = std::system("ps aux | grep nginx");  // Linux / Mac
    // WinExec("cmd", 1);     // Win

    // Get the output of CMDs
    // std::string outputs = exec("ps aux | grep MediaServer");  // Linux / Mac

    // [!] When running a program using CMD in c++ code, this main thread will be stucked
    //     and wait for the end of this execution. To prevend this, use thread
    // std::system("cd /home/kcl/Documents/algorithm/adasAlgo && ./build/bin/serverController");
    // std::string outputs = exec("cd /home/kcl/Documents/algorithm/adasAlgo && ./build/bin/serverController");
    // std::system("./cmd.sh");

    std::thread worker(exec, "cd /home/kcl/Documents/algorithm/adasAlgo/ && ./scripts/zlmedia.sh /home/kcl/Documents/libs/ZLMediaKit/release/linux/Debug");
    // std::thread worker(exec, "./cmd.sh jetson 123456 0");
    // worker.join();
    worker.detach();

    // This program should wait for a time period or the target program will not be started
    usleep(5 * 1000 * 1000);    // 1s


    print("=====");
    // print(outputs);
    // print(outputs.size());
    return 0;
}
