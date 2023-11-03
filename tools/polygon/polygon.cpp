
#include "polygon.h"


Polygon::Polygon()
{

}


Polygon::~Polygon()
{

}


bool Polygon::isInArea(std::vector<std::vector<double>>& ps, 
                       std::vector<double>& p, int num_corner)
{
    int nCross = 0;
    int corner = (num_corner <= ps.size()) ? num_corner : ps.size();

    for (int i = 0; i < corner; i++) {
        std::vector<double> p1 = ps[i];
        std::vector<double> p2 = ps[(i + 1) % corner];

        if (p1[1] == p2[1])  // the border is parallel with the ray
            continue;

        if (p[1] < std::min(p1[1], p2[1]))  // the ray cross below the border
            continue;

        if (p[1] >= std::max(p1[1], p2[1]))  // the ray cross above the border
            continue;

        double x = (p[1] - p1[1]) * (p2[0] - p1[0]) / (p2[1] - p1[1]) + p1[0];
        if (x >= p[0])
            nCross++;  // only one side of cross point will be counted
    }

    return (nCross % 2 == 1);
}

