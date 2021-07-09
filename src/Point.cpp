#include "Point.hpp"

using namespace std;

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