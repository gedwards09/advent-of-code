#include <cassert>
#include <iostream>

#include "HashableCoordinatePair.h"

HashableCoordinatePair::HashableCoordinatePair(HashableCoordinate* left, HashableCoordinate* right) : 
        Pair<HashableCoordinate>(left, right),
        _dist(HashableCoordinatePair::ConstructSquaredDistance(left, right)) {  }

long long HashableCoordinatePair::ConstructSquaredDistance(ICoordinate* left, ICoordinate* right)
{
    return left->SquaredDistance(right);
}

/** Simply returning the difference might overflow an int here */
int HashableCoordinatePair::CompareTo(HashableCoordinatePair* other) const
{
    long long diff;
    
    assert(other != NULL);
    diff = this->_dist - other->_dist;
    
    return (diff > 0) - (diff < 0);
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