
// Bug remains when computing the following matrix:
// Array<int, 4, 4, RowMajor> m1;
// m1 <<  4,  2,  5,  7,
//        8,  3, 10,  8,
//       12,  5,  4,  5,
//        6,  3,  7, 12;

#ifndef _TESTLIB_H
#define _TESTLIB_H

#include <chrono>
#include <iostream>

#include "assign/munkres.h"

#define print(x) std::cout << x << std::endl;

using namespace Eigen;


class TestLibs
{
public:
    TestLibs();
    ~TestLibs();

    int munkres();

    int kalman();
    int lowpass();
    int filtfilt();
    int butterworth();

private:

};


#endif // _TESTLIB_H
