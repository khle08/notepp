
// link: https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

#include <map>
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
    std::string partial;

    while (end != std::string::npos)
    {
        partial = str.substr(start, end - start);
        if (partial.size() >= 1) {
            // This is used to filter out a series of space such that "    "
            strVec.push_back(partial);
        }
        // strVec.push_back(str.substr(start, end - start));
        // print(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    partial = str.substr(start, end - start);
    if (partial.size() >= 1) {
        // This is used to filter out a series of space such that "    "
        strVec.push_back(partial);
    }
    // strVec.push_back(str.substr(start, end - start));
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


int bluetoothInfo(std::string line, std::pair<std::string, std::string>& p)
{
    int io = -1;
    std::string mac = "";   // p.first
    std::string name = "";  // p.second

    std::vector<std::string> v;
    if (line.find(":") != std::string::npos) {
        // Get the last part of bluetooth name
        strSplit(line, ":", v);
        name = v[v.size() - 1];
        name = name.substr(3, name.size());
        p.first = name;
    } else {
        return io;
    }

    // Get the MAC address for each device
    std::vector<std::string> m;
    strSplit(line, " ", m);

    for (int i = 0; i < m.size(); i++) {
        if (m[i].find(":") != std::string::npos) {
            mac = m[i];
            p.second = mac;
            io = 0;
            break;
        }
    }

    return io;
}


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

    // [!] Wifi test
    std::string outputs = exec("./cmd.sh");
    std::vector<std::string> strVecWifi;
    strSplit(outputs, "\n", strVecWifi);
    print(strVecWifi[0]);

    // Json::Value wifiData;
    for (int i = 1; i < strVecWifi.size(); i++) {
        int wifi_now = 0;

        std::vector<std::string> names;
        strSplit(strVecWifi[i], " ", names);
        if (names.size() == 10) {
            wifi_now = 1;
        }

        // wifiData["status"].append(wifi_now);
        // wifiData["name"].append(names[0 + wifi_now]);
        // wifiData["mode"].append(names[1 + wifi_now]);
        // wifiData["chan"].append(names[2 + wifi_now]);
        // wifiData["rate"].append(names[3 + wifi_now]);
        // wifiData["signal"].append(names[5 + wifi_now]);
        // wifiData["security"].append(names[7 + wifi_now] + "/" + names[8 + wifi_now]);

        std::string wifi_name = names[0 + wifi_now];
        std::string wifi_mode = names[1 + wifi_now];
        std::string wifi_chan = names[2 + wifi_now];
        std::string wifi_rate = names[3 + wifi_now];
        std::string wifi_signal = names[5 + wifi_now];
        std::string wifi_security = names[7 + wifi_now] + "/" + names[8 + wifi_now];
        // print(wifi_name << " "  << wifi_mode << " " << wifi_chan << " " << wifi_rate << " " << wifi_signal << " " << wifi_security);
    }


    // // [!] Bluetooth test
    // std::string outputs = exec("./cmd.sh");
    // // [NEW] Controller C8:FF:28:78:1B:94 kcl [default]
    // // [NEW] Device 34:88:5D:42:66:2B Keyboard K380
    // // [NEW] Device F4:AF:E7:5A:EA:2D Jack‘s AirPods
    // // Agent registered
    // // [bluetooth]# quit
    // // Agent unregistered
    // // [DEL] Controller C8:FF:28:78:1B:94 kcl [default]
    // print(outputs);

    // std::vector<std::string> strVec;
    // strSplit(outputs, "\n", strVec);
    // // print("[start]\n" << strVec[0] << "\n[end]");

    // print("======");
    // for (int i = 0; i < strVec.size(); i++) {
    //     std::pair<std::string, std::string> data;
    //     int res = bluetoothInfo(strVec[i], data);
    //     if (res == 0) {
    //         print(data.second << " <- " << data.first);
    //     }
    // }

    // std::thread worker(exec, "cd /home/kcl/Documents/algorithm/adasAlgo/ && ./scripts/zlmedia.sh /home/kcl/Documents/libs/ZLMediaKit/release/linux/Debug");
    // // std::thread worker(exec, "./cmd.sh jetson 123456 0");
    // // worker.join();
    // worker.detach();

    // This program should wait for a time period or the target program will not be started
    // usleep(5 * 1000 * 1000);    // 1s


    print("=====");
    // print(outputs);
    // print(outputs.size());
    return 0;
}
