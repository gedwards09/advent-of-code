#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Coordinate.h"

Coordinate::Coordinate() : Coordinate(0, Coordinate::s_defaultValue, Coordinate::s_defaultValue, Coordinate::s_defaultValue) {  }

Coordinate::Coordinate(int x) : Coordinate(1, x, Coordinate::s_defaultValue, Coordinate::s_defaultValue) {  }

Coordinate::Coordinate(int x, int y) : Coordinate(2, x, y, Coordinate::s_defaultValue) {  }

Coordinate::Coordinate(int x, int y, int z) : Coordinate(3, x, y, z) {  }

Coordinate::Coordinate(size_t szArr, int x, int y, int z) : _sz(szArr), _array{x, y, z}
{
    assert(this->_sz <= MAX_DIM);
}

int Coordinate::X() const
{
    return this->getAtPos(XIDX);
}

int Coordinate::Y() const
{
    return this->getAtPos(YIDX);
}

int Coordinate::Z() const
{
    return this->getAtPos(ZIDX);
}

int Coordinate::getAtPos(size_t i) const
{
    assert(this->_sz > i);
    return this->_array[i];

}

size_t Coordinate::Size() const
{
    return this->_sz;
}

int* Coordinate::Serialize(int arr[], size_t szArr) const
{
    assert(szArr >= this->_sz);
    memcpy(arr, this->_array, sizeof(int) * this->_sz);
    for (size_t sz = this->_sz; sz < szArr; sz++)
    {
        arr[sz] = 0;
    }
    return arr;
}

long long Coordinate::SquaredDistance(ICoordinate* other) const
{
    long long out;

    assert(this->_sz == other->Size());
    out = 0;
    out += (this->X() - other->X()) * (long long)(this->X() - other->X());
    out += (this->Y() - other->Y()) * (long long)(this->Y() - other->Y());
    out += (this->Z() - other->Z()) * (long long)(this->Z() - other->Z());

    return out;
}

void Coordinate::Print() const
{
    std::cout << "( ";
    for (size_t i = 0; i < this->_sz; i++)
    {
        if (i > 0)
        {
            std::cout << ", ";
        }
        std::cout << this->_array[i];
    }
    std::cout << " )";
}