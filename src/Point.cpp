#include "Point.hpp"

using namespace std;

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(int nx, int ny)
{
    this->x = nx;
    this->y = ny;
}

// Printing a Point.
std::ostream &operator<<(std::ostream &o, Point const *p)
{
    return o << "(" << p->x << ", " << p->y << ")";
}