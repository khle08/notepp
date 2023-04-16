
#include "clock.h"


Timer::Timer()
{

}


Timer::~Timer()
{
    
}


int Timer::getTime()
{
    std::time_t t = std::time(nullptr);
    struct std::tm *ptm = std::localtime(&t);
    std::stringstream stream;
    stream << std::put_time(ptm, "%Y:%m:%d:%H:%M:%S");

    std::string stm = stream.str();
    std::vector<std::string> YMDHMS;
    strSplit(stm, ":", YMDHMS);

    Y = std::stoi(YMDHMS[0]);
    M = std::stoi(YMDHMS[1]);
    D = std::stoi(YMDHMS[2]);

    h = std::stoi(YMDHMS[3]);
    m = std::stoi(YMDHMS[4]);
    s = std::stoi(YMDHMS[5]);
    return 0;
}


int Timer::getSeconds()
{
    sec = 3600 * h + 60 * m + s;
    return sec;
}


int Timer::now(std::string mode)
{
    if (mode == "start") {
        gettimeofday(&t_start, 0);
    } else if (mode == "end") {
        gettimeofday(&t_end, 0);
    } else {
        return -1;
    }

    return 0;
}


double Timer::getMilliSeconds()
{
    float t = ( t_end.tv_sec -  t_start.tv_sec) * 1000.0f + 
              (t_end.tv_usec - t_start.tv_usec) / 1000.0f;
    return (double)t;
}


double Timer::getMicroSeconds()
{
    float t = ( t_end.tv_sec -  t_start.tv_sec) * 1000000.0f + 
              (t_end.tv_usec - t_start.tv_usec);
    return (double)t;
}

