#ifndef _PARAM_H_
#define _PARAM_H_

#include <map>
#include <regex>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


#define print(x) std::cout << x << std::endl


class Param
{
public:
    Param(std::string file, bool save);
    ~Param();

    int totalParam;
    bool saveBack;
    std::string fileName;

    int keyExist(std::string key);
    std::string getValue(std::string key);

    int setValue(std::string key, std::string value);
    int updateValue(std::string key, std::string value);

    int saveParams();

private:
    int maxSpace = 50;
    std::map<std::string, std::string> params;

};


#endif // _PARAM_H_

