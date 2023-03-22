#ifndef POINT_HPP
#define POINT_HPP

#include "HalfEdge.hpp"

class Point
{
public:
    double x, y;
    HalfEdge* incident_edge;
    Point(double a = 0, double b = 0)
    {
        x = a;
        y = b;
        incident_edge = nullptr;
    }
};

#endif