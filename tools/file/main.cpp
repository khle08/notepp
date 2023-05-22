
#include "files.h"


int main(int argc, char** argv)
{
	std::string cmd = "mkdir ";
	std::string f = "output";
	std::string c = cmd + f;
	std::system((cmd + f).c_str());

	std::vector<std::string> strlist;
	strlist.push_back("this is great");
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
    ret = getFileList(filePath, fileList, false, ".txt");
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