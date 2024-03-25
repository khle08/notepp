
// link: https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"
// #include <windows.h>

#define print(x) std::cout << x << std::endl


int strSplit(std::string& str, std::string delim, std::vector<std::string>& strVec)
{
    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos)
    {
        strVec.push_back(str.substr(start, end - start));
        // print(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    strVec.push_back(str.substr(start, end - start));
    return 0;
}


std::string exec(const char* cmd)
{
    // [!] This func can only run "non-sudo" cmd. 
    //     To check fun that can run "sudo" cmd, go to "tools/daemon/main.cpp"

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

    std::string outputs = exec("./cmd.sh");
    // [NEW] Controller C8:FF:28:78:1B:94 kcl [default]
    // [NEW] Device 34:88:5D:42:66:2B Keyboard K380
    // [NEW] Device F4:AF:E7:5A:EA:2D Jack‘s AirPods
    // Agent registered
    // [bluetooth]# quit
    // Agent unregistered
    // [DEL] Controller C8:FF:28:78:1B:94 kcl [default]

    std::vector<std::string> strVec;
    strSplit(outputs, "\n", strVec);
    // print("[start]\n" << strVec[0] << "\n[end]");

    for (int i = 0; i < strVec.size(); i++) {
        std::vector<std::string> v;
        if (strVec[i].find(":") != std::string::npos) {
            // Get the last part of bluetooth name
            strSplit(strVec[i], ":", v);
            std::string name = v[v.size() - 1];
            name = name.substr(3, name.size());
            print(name);
        }

        // Get the MAC address for each device
        std::vector<std::string> m;
        strSplit(strVec[i], " ", m);
        std::string mac;

        for (int i = 0; i < m.size(); i++) {
            if (m[i].find(":") != std::string::npos) {
                mac = m[i];
                print(mac);
                break;
            }
        }
    }

    // std::thread worker(exec, "cd /home/kcl/Documents/algorithm/adasAlgo/ && ./scripts/zlmedia.sh /home/kcl/Documents/libs/ZLMediaKit/release/linux/Debug");
    // // std::thread worker(exec, "./cmd.sh jetson 123456 0");
    // // worker.join();
    // worker.detach();

    // This program should wait for a time period or the target program will not be started
    usleep(5 * 1000 * 1000);    // 1s


    print("=====");
    // print(outputs);
    // print(outputs.size());
    return 0;
}
