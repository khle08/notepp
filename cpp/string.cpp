// Note: part of string funcs are defined in "tools/files.cpp"

#include <string>
#include <vector>
#include <sstream>     // for "std::stringstream"
#include <iostream>    // for "std::cout"


#define print(x) std::cout << x << std::endl


bool is_number(std::string &s) {
    return s.find_first_not_of("0123456789") == std::string::npos;
}

std::string strConcat(std::vector<std::string> strVec)
{
    std::stringstream stream;
    for (auto s: strVec) {
        stream << s;
    }
    return stream.str();
}


std::string zeroFmt(int num, int n)
{
    // input: zeroFmt(4, 23); output: "0023"

    std::string s = std::to_string(n);
    if (num > s.length()) {
        return std::string(num - s.length(), '0') + s;
    } else {
        return std::to_string(n);
    }
}


int strFind()
{
    std::string str ("There are two needles in this haystack with needles.");
    std::string str2 ("needle");

    // different member versions of find in the same order as above:
    std::size_t found = str.find(str2);
    if (found != std::string::npos)
        print("first 'needle' found at: " << found);

    found = str.find("needles are small", found + 1, 6);
    if (found!=std::string::npos)
        print("second 'needle' found at: " << found);

    found = str.find("haystack");
    if (found != std::string::npos)
        print("'haystack' also found at: " << found);

    found = str.find('.');
    if (found != std::string::npos)
        print("Period found at: " << found);

    // let's replace the first needle:
    str.replace(str.find(str2), str2.length(), "preposition");
    std::cout << str << '\n';

    return 0;
}


int main()
{
    const char *e = "char";
    std::string s = "string";
    print(s + e);  // can add them together

    char buffer[100];
    int age = 23;

    sprintf(buffer, "my age is %d", age);
    print(buffer);
    std::string sbuffer(buffer);
    std::string sbuffer1 = "my age is 23";
    print(sbuffer.compare(sbuffer1));  // 0: equal / other number: not equal

    bool aaa = true;
    bool bbb = false;
    bool ccc = !bbb;
    print(!aaa);  // 0 false
    print(!bbb);  // 1 true
    print(!ccc << "\n---");  // 0 false

    int xxx = 1;
    int yyy = 0;

    print(!xxx);

    // Concate the string list altogether
    // std::vector<std::string> sv = {"1920", "x", "1080"};
    // std::string s1 = strConcat({1920, "x", 1080});
    // print(s1.c_str());
    // strFind();

    return 0;
}

