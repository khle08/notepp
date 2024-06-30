
// [!] For linux
#include <iostream>
#include <string>
#include <unistd.h>
#include <limits.h>

std::string getCurrentWorkingDirectory() {
    char temp[PATH_MAX];
    if (getcwd(temp, PATH_MAX) != NULL) {
        return std::string(temp);
    } else {
        // Handle error
        return "";
    }
}

int main() {
    std::string currentDirectory = getCurrentWorkingDirectory();
    std::cout << "Current working directory: " << currentDirectory << std::endl;
    return 0;
}


// [!] For windows
// #include <iostream>
// #include <string>
// #include <windows.h>

// std::string getCurrentWorkingDirectory() {
//     char temp[MAX_PATH];
//     if (GetCurrentDirectory(MAX_PATH, temp)) {
//         return std::string(temp);
//     } else {
//         // Handle error
//         return "";
//     }
// }

// int main() {
//     std::string currentDirectory = getCurrentWorkingDirectory();
//     std::cout << "Current working directory: " << currentDirectory << std::endl;
//     return 0;
// }
