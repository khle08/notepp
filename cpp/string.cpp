// Note: part of string funcs are defined in "tools/files.cpp"

#include <string>
#include <vector>
#include <sstream>     // for "std::stringstream"
#include <iostream>    // for "std::cout"


#define print(x) std::cout << x << std::endl


std::string strConcat(std::vector<std::string> strVec)
{
    std::stringstream stream;
    for (auto s: strVec) {
        stream << s;
    }
    return stream.str();
}


int main()
{
    char buffer[100];
    int age = 23;

    sprintf(buffer, "my age is %d", age);
    print(buffer);


    // Concate the string list altogether
    // std::vector<std::string> sv = {"1920", "x", "1080"};
    std::string s1 = strConcat({"1920", "x", "1080"});

    print(s1.c_str());

    return 0;
}

