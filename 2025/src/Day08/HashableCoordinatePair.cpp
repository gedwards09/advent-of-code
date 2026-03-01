#include <cassert>
#include <iostream>

#include "HashableCoordinatePair.h"

HashableCoordinatePair::HashableCoordinatePair(IHashableCoordinate* left, IHashableCoordinate* right) : 
        Pair<IHashableCoordinate>(left, right),
        _dist(HashableCoordinatePair::ConstructSquaredDistance(left, right)) {  }

long long HashableCoordinatePair::ConstructSquaredDistance(ICoordinate* left, ICoordinate* right)
{
    return left->SquaredDistance(right);
}

int HashableCoordinatePair::CompareTo(HashableCoordinatePair* other)
{
    assert(other != NULL);
    if (this->_dist == other->_dist)
    {
        return 0;
    }
    else if (this->_dist > other->_dist)
    {
        return 1;
    }
    else // this->_dist < other->_dist
    {
        return -1;
    }
}

long long HashableCoordinatePair::GetSquaredDistance() const
{
    return this->_dist;
}

void HashableCoordinatePair::Print() const
{
    this->GetLeft()->Print();
    std::cout << " ";
    this->GetRight()->Print();
    std::cout << ' ' << this->_dist << std::endl;
}