#include <iostream>
using namespace std;

class Point
{
public:
    int x, y;

    Point(int nx, int ny);

    // Printing a Point.
    friend std::ostream &operator<<(std::ostream &o, Point const *p);
};