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

#define print(x) std::cout << x << std::endl
// using namespace std;


// ref: https://blog.csdn.net/m0_37263637/article/details/79443429
int getFileList(std::string dirent, std::vector<std::string> &FileList, 
                bool fullPth, std::string key)
{
    DIR *p_dir;
    struct dirent *p_dirent;

    if((p_dir = opendir((dirent).c_str())) == nullptr){
        print("check pir path: " << (dirent).c_str() << " failed");
        return -1;
    }
    while((p_dirent=readdir(p_dir)))
    {
        std::string s(p_dirent->d_name);
        if(s != "." && s != "..") {
            std::size_t found = s.find(key);
            if (found == std::string::npos) {
                continue;
            }

            if (fullPth) {
                FileList.push_back(dirent + s);
            } else {
                FileList.push_back(s);
            }
        }
    }
    closedir(p_dir);
    std::sort(FileList.begin(), FileList.end());
    return FileList.size();
}


template<typename T>
int writeFile(std::string fileName, std::vector<T> &dataList)
{
    // ref: https://www.cnblogs.com/helinsen/archive/2012/07/26/2609251.html
    // std::ios::in             读
    // std::ios::out            写
    // std::ios::app            从文件末尾开始写
    // std::ios::binary         二进制模式
    // std::ios::nocreate       打开一个文件时，如果文件不存在，不创建文件。
    // std::ios::noreplace      打开一个文件时，如果文件不存在，创建该文件
    // std::ios::trunc          打开一个文件，然后清空内容
    // std::ios::ate            打开一个文件时，将位置移动到文件尾

    // write something to the fileName.
    std::ofstream outFile(fileName, std::ios::out);

    for (T data : dataList)
    {
        outFile << data << "\n";
    }
    outFile.close();
    return 0;
}


int readFile(std::string fileName)
{
	std::ifstream inFile(fileName, std::ios::in);

	// if a string type object is used to hold the content this way,
	// it will be a vocabulary interrupted by "space".
    std::string str;
    inFile >> str;
    print(str);
    // if the step is repeated again, str will get the next vocabulary automatically.
    inFile >> str;
    print(str);

    // if a char is used to hold the content on the other hand,
    // only 1 character will be recorded once a time.
	char ch;
	inFile >> ch;
	print("char: " << ch);

	// if we want to get the whole line, use this.
    std::string line;
    getline(inFile, line);
    print(line);
    getline(inFile, line);
    print(line);

	return 0;
}


int strReplace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return 0;
    str.replace(start_pos, from.length(), to);
    return 0;
}


std::string strConcat(std::vector<std::string> strVec)
{
    std::stringstream stream;
    for (auto s: strVec) {
        stream << s;
    }
    return stream.str();
}


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


std::string dirName(std::string dir, bool full_path = true)
{
	std::vector<std::string> folders;
	strSplit(dir, "/", folders);
	std::string dirName = folders[folders.size() - 2];

	if (!full_path)
		return dirName;

	strReplace(dir, folders[folders.size() - 1], "");
	return dir;
}


int main(int argc, char** argv)
{
	std::string cmd = "mkdir ";
	std::string f = "output";
	std::string c = cmd + f;
	std::system((cmd + f).c_str());

	std::vector<std::string> strlist(5);
	strlist.push_back("this is great\n");
	strlist.push_back("you look good");

	writeFile("test.txt", strlist);
    readFile("test.txt");
    print(" ");

    std::string strTest = "this/is/one/path.csv";
    print(dirName(strTest, true));
    strReplace(strTest, ".csv", ".txt");
    print(strTest);
    strTest = std::regex_replace(strTest, std::regex("/one"), "/two");
    print(strTest);

    std::vector<std::string> split;
    strSplit(strTest, "/", split);
    print(split.size());
    print(" ");

    std::string filePath;
    int ret = 0;
    if(argc > 1){
        filePath= argv[1];//.c_str();
        print("filePath: " << filePath);
        // cout << "filePath:" << filePath << endl;
    }
    else{
    	print("please input file path.");
        // cout << "please input file path." << endl;
        return -1;
    } 
    std::vector<std::string> fileList;
    ret = getFileList(filePath, fileList);
    if(ret < 0)
        return -1;

    print("fileList:");
    // cout << "fileList:" << endl;
    for(auto imageName : fileList)
    {
        std::string imagePath = filePath + imageName;
        print(imagePath);
        // cout << imagePath << endl;
    }
    return 0;
}