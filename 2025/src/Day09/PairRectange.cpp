#include "PairRectangle.h"

PairRectangle::PairRectangle(int i, int j, long long area) : _i(i), _j(j), _area(area) {  }

int PairRectangle::CompareTo(PairRectangle* other) const
{
    long long diff;

    diff = this->longCompareTo(other);

    return (diff > 0) - (diff < 0);
}

int PairRectangle::GetIndexI() const
{
    return this->_i;
}

int PairRectangle::GetIndexJ() const
{
    return this->_j;
}

long long PairRectangle::GetArea() const
{
    return this->_area;
}

long long PairRectangle::longCompareTo(PairRectangle* other) const
{
    return this->_area - other->_area;
}