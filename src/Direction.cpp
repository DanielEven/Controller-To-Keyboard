#include "Direction.hpp"
#include <stdexcept>

Direction::Direction() : Point()
{
}

Direction::Direction(int dx, int dy) : Point(dx, dy)
{
    if (dx > 1 || -1 > dx || dy > 1 || -1 > dy)
    {
        throw std::invalid_argument("The x and y values should be between -1 and 1.");
    }
}