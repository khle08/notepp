
#include "timer.h"


int strSplit(std::string& str, std::string delim, std::vector<std::string>& strVec)
{
    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos)
    {
        strVec.push_back(str.substr(start, end - start));
        // print(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    strVec.push_back(str.substr(start, end - start));
    return 0;
}


std::string Time::getTime()
{
    std::time_t t = std::time(nullptr);
    struct std::tm *ptm = std::localtime(&t);
    std::stringstream stream;
    stream << std::put_time(ptm, "%Y:%m:%d:%H:%M:%S");

    std::string stm = stream.str();
    std::vector<std::string> YMDHMS;
    strSplit(stm, ":", YMDHMS);

    Y = std::stoi(YMDHMS[0]);  // year
    M = std::stoi(YMDHMS[1]);  // month
    D = std::stoi(YMDHMS[2]);  // day

    h = std::stoi(YMDHMS[3]);  // hour
    m = std::stoi(YMDHMS[4]);  // minute
    s = std::stoi(YMDHMS[5]);  // second

    std::string info = zeroFmt(4, Y) + "-" + zeroFmt(2, M) + "-" + zeroFmt(2, D);
    info += "_" + zeroFmt(2, h) + "-" + zeroFmt(2, m) + "-" + zeroFmt(2, s);
    return info;
}


int Time::getSeconds()
{
    sec = 3600 * h + 60 * m + s;
    return sec;
}


int Time::now(std::string mode)
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


double Time::getMilliSeconds()
{
    float t = ( t_end.tv_sec -  t_start.tv_sec) * 1000.0f + 
              (t_end.tv_usec - t_start.tv_usec) / 1000.0f;
    return (double)t;
}


double Time::getMicroSeconds()
{
    float t = ( t_end.tv_sec -  t_start.tv_sec) * 1000000.0f + 
              (t_end.tv_usec - t_start.tv_usec);
    return (double)t;
}


std::string Time::zeroFmt(int num, int n)
{
    std::string s = std::to_string(n);
    if (num > s.length()) {
        return std::string(num - s.length(), '0') + s;
    } else {
        return std::to_string(n);
    }