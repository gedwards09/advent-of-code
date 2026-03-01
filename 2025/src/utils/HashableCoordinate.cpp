#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Hasher.h"

#include "HashableCoordinate.h"

HashableCoordinate::~HashableCoordinate()
{
    delete this->_coord;
}

HashableCoordinate::HashableCoordinate(ICoordinate* coord) : 
        _coord(coord), _hash(HashableCoordinate::ConstructHash(coord)) {  }

hash_t HashableCoordinate::ConstructHash(ICoordinate* coord)
{
    assert(coord != NULL);

    int serializedData[SZ_MAX_ARR];
    int szData;
    int* _;

    szData = coord->Size();
    _ = coord->Serialize(serializedData, szData);

    return Hasher::Hash((unsigned char*)serializedData, sizeof(int) * szData);
}

int HashableCoordinate::X() const
{
    return this->_coord->X();
}

int HashableCoordinate::Y() const
{
    return this->_coord->Y();
}

int HashableCoordinate::Z() const
{
    return this->_coord->Z();
}

size_t HashableCoordinate::Size() const
{
    return this->_coord->Size();
}

int* HashableCoordinate::Serialize(int arr[], size_t sz) const
{
    return this->_coord->Serialize(arr, sz);
}

long long HashableCoordinate::SquaredDistance(ICoordinate* other) const
{
    return this->_coord->SquaredDistance(other);
}

void HashableCoordinate::Print() const
{
    this->_coord->Print();
}

hash_t HashableCoordinate::Hash() const
{
    return this->_hash;
}