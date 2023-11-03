#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <cmath>
#include <vector>
#include <string>
#include <iostream>


#define print(x) std::cout << x << std::endl


class Polygon
{
public:
    Polygon();
    ~Polygon();

    bool isInArea(std::vector<std::vector<double>>& ps, 
                  std::vector<double>& p, int num_corner);

private:
    int sec = 0;

};


#endif // _POLYGON_H_

