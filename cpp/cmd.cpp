
// link: https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

#include <string>
#include <iostream>
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
    // int s = std::system("ps aux | grep nginx");  // Linux / Mac
    // WinExec("cmd", 1);     // Win

    // Get the output of CMDs
    std::string outputs = exec("ps aux | grep nginx");  // Linux / Mac

    print("=====");
    print(outputs);
    print(outputs.size());
    return 0;
}
