#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/time.h>


#define print(x) std::cout << x << std::endl


class Polygon
{
public:
    int Y, M, D, h, m, s;

private:
    int sec = 0;

};


#endif // _POLYGON_H_

