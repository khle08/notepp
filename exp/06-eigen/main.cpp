
#include <chrono>
#include <iostream>

#include "test.h"

#define print(x) std::cout << x << std::endl;


int main(int argc, char const *argv[])
{
    print("\n===== Eigen/Dense testing [start] =====");
    TestLibs* t = new TestLibs();
    // t->munkres();
    t->matrixTest();

    delete t;
    print("===== Eigen/Dense testing [ end ] =====\n");

    return 0;
}

