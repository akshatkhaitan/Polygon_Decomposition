
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "Point.hpp"

class Rectangle
{
public:
    double x_max, y_max, x_min, y_min;
    Rectangle();
    void setLimit(Point *p);
    bool checkInside(Point *p);    
};

Rectangle::Rectangle()
{
    x_max = INT_MIN;
    y_max = INT_MIN;
    x_min = INT_MAX;
    y_min = INT_MAX;
}

void Rectangle::setLimit(Point *p)
{
    x_max = max(x_max, p->x);
    y_max = max(y_max, p->y);
    x_min = min(x_min, p->x);
    y_min = min(y_min, p->y);
}

bool Rectangle::checkInside(Point *p)
{
    if (p->x > x_min && p->x < x_max && p->y > y_min && p->y < y_max)
        return true;
    return false;
}

#endif