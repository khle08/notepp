
#include "polygon.h"


int main()
{
    print("successful compilation!");

    Polygon polygon;

    // sequence: (x, y), (x, y), ...
    std::vector<std::vector<double>> points = {
        {-5,  0},
        { 0,  5},
        { 2, 10},
        { 5,  5},
        { 8,  0},
        { 5, -3},
        { 2,  0},
        { 0, -5}
    };

    std::vector<double> p = {2, -1};

    bool ans = polygon.isInArea(points, p, 8);
    print(ans);

    return 0;
}



