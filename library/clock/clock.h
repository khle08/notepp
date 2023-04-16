#ifndef _CLOCK_H
#define _CLOCK_H

#include <iomanip> 
#include <iostream>
#include <sys/stat.h>
#include <sys/time.h>

#define print(x) std::cout << x << std::endl


class Timer
{
public:
    Timer();
    ~Timer();

    int getTime();
    int getSeconds();

    int now(std::string mode);
    double getMilliSeconds();
    double getMicroSeconds();

private:
    int sec = 0;
    double msec = 0.0;
    double usec = 0.0;
    int Y, M, D, h, m, s;

    struct timeval t_start;
    struct timeval t_end;
};


#endif /* _CLOCK_H */
