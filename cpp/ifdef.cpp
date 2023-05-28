
#include <iostream>
#include <string>
#include <vector>

// this can only be used since C++14
#include <memory>    // For shared pointer

#define print(x) std::cout << x << std::endl

// #define DEBUG false  // success
// int DEBUG = 0;       // failed


int main()
{
    #define DEBUG   // success
    
#ifdef DEBUG
    print("debug");
#else
    print("release");
#endif

    std::string s1 = "abc";
    bool res = s1.data() == s1.c_str();
    print(res);

    int isAndroid = std::stoi("0");
    if (isAndroid == 1) {
    	#define ANDROID 1
    }

#if 1
    print("this is android");
#else
    print("else");
#endif

    return 0;
}

