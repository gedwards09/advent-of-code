#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) : _x(x), _y(y) {  }

int Coordinate::X()
{
    return this->_x;
}

int Coordinate::Y()
{
    return this->_y;
}