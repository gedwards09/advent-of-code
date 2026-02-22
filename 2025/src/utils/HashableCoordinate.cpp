#include "Hasher.h"
#include "HashableCoordinate.h"

HashableCoordinate::HashableCoordinate(int x, int y) : Coordinate(x, y)
{  
    int serializedData[SZ_HASHABLE_COORDINATE_DATA];
    serializedData[0] = x;
    serializedData[1] = y;
    this->_hash = Hasher::Hash((unsigned char*)serializedData, sizeof(int) * SZ_HASHABLE_COORDINATE_DATA);
}

hash_t HashableCoordinate::Hash()
{
    return this->_hash;
}