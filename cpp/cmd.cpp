
// link: https://stackoverflow.com/questions/31201631/execute-cmd-commands-using-c

#include <iostream>
// #include <windows.h>


int main() {
    std::system("echo abc");  // Linux / Mac
    // WinExec("cmd", 1);     // Win
    return 0;
}
