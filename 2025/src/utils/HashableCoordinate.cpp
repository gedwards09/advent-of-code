#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Hasher.h"

#include "HashableCoordinate.h"

HashableCoordinate::HashableCoordinate() : 
        Coordinate(), _hash() {  }

HashableCoordinate::HashableCoordinate(int x) : 
        Coordinate(x), _hash(HashableCoordinate::ConstructHash(this)) {  }

HashableCoordinate::HashableCoordinate(int x, int y) : 
        Coordinate(x, y), _hash(HashableCoordinate::ConstructHash(this)) {  }

HashableCoordinate::HashableCoordinate(int x, int y, int z) : 
        Coordinate(x, y, z), _hash(HashableCoordinate::ConstructHash(this)) {  }

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

hash_t HashableCoordinate::Hash() const
{
    return this->_hash;
}