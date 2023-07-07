#ifndef _FILES_H_
#define _FILES_H_

// #include <stdio.h>
// #include <dirent.h>


// ref: http://www.lucasgabrieltutors.weinode.com/articles/71
// int main(int argc, const char * argv[]) {
    
//     struct dirent *dirp;
    
//     DIR* dir = opendir("./");
    
//     while ((dirp = readdir(dir)) != nullptr) {
//         if (dirp->d_type == DT_REG) {
//             // 文件
//             printf("file %s\n", dirp->d_name);
            
//         } else if (dirp->d_type == DT_DIR) {
//             // 文件夹
//             printf("dir %s\n", dirp->d_name);
//         }
//     }
    
//     closedir(dir);
    
    
//     return 0;
// }

#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>     // for "std::stringstream"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>


#define print(x) std::cout << x << std::endl


int getFileList(std::string dirent, std::vector<std::string> &FileList, bool fullPth, std::string key);

// template<typename T>
int writeFile(std::string fileName, std::vector<std::string> &dataList);
int readFile(std::string fileName);

int strReplace(std::string& str, const std::string& from, const std::string& to);
std::string strConcat(std::vector<std::string> strVec);
int strSplit(std::string& str, std::string delim, std::vector<std::string>& strVec);
int strip(std::string& str);

std::string dirName(std::string dir, bool full_path = true);
bool fileExist(const std::string& name);
bool dirExist(const std::string& name);
int makedirs(std::string pth);


#endif // _FILES_H_

