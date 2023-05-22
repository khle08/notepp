
#include "files.h"


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


// template<typename T>
int writeFile(std::string fileName, std::vector<std::string> &dataList)
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

    for (std::string data : dataList)
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


std::string dirName(std::string dir, bool full_path)
{
	std::vector<std::string> folders;
	strSplit(dir, "/", folders);
	std::string dirName = folders[folders.size() - 2];

	if (!full_path)
		return dirName;

	strReplace(dir, folders[folders.size() - 1], "");
	return dir;
}


bool fileExist(const std::string& name)
{
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}


int makedirs(std::string pth)
{
    std::vector<std::string> strVec;
    strSplit(pth, "/", strVec);

    int res;
    int count = 0;
    std::string recursive = "";
    for (int i = 0; i < strVec.size(); i++) {
        if (strVec[i] != ".") {
            recursive += strVec[i] + "/";
            res = mkdir(recursive.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            count += 1;
        }
    }

    if (count == 0) {
        print("[ERROR] Invalid path");
        return -1;
    }
    return 0;
}

