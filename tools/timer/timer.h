#ifndef _TIMER_H_
#define _TIMER_H_

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/time.h>


#define print(x) std::cout << x << std::endl


class Time
{
public:
    int Y, M, D, h, m, s;

    int getTime();
    int getSeconds();

    int now(std::string mode);
    double getMilliSeconds();
    double getMicroSeconds();

private:
    int sec = 0;
    double msec = 0.0;
    double usec = 0.0;

    struct timeval t_start;
    struct timeval t_end;
};


#endif // _TIMER_H_

