
#include <unistd.h>

#include "timer.h"

int main()
{
    Time TimeSelf;
    double move_time = 0.0;

    TimeSelf.now("start");
    usleep(1 * 1000 * 1000);  // 1s

    std::string s1 = TimeSelf.getTime();
    print(s1);
    print(TimeSelf.Y << "/" << TimeSelf.M << "/" << TimeSelf.D);

    usleep(1 * 1000 * 1000);  // 1s
    TimeSelf.now("end");

    move_time += TimeSelf.getMilliSeconds() / 1000.0;

    print(move_time);

    std::string s2 = TimeSelf.getTime();
    print(s2);

    usleep(3 * 1000 * 1000);

    std::string s3 = TimeSelf.getTime();
    print(s3);

    return 0;
}



