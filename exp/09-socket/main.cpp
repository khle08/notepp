
#include <map>
#include <thread>
#include <string>
#include <iostream>
#include <unistd.h>    // for "usleep"

#include "server.h"
#include "client.h"

#define print(x) std::cout << x << std::endl;


int main(int argc, char const *argv[])
{

    print("\n===== Socket testing [start] =====");


    print(  "===== Socket testing [ end ] =====\n");

    return 0;
}
