// g++ bytes.cpp -o bytes -liconv

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

#define print(x) std::cout << x << std::endl;


int main()
{ 
    int i = 0;
    while (true) {
        i += 100;
        print(i);
    }

    return 0;
}


