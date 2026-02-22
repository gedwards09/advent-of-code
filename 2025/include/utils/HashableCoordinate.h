#ifndef __HASHABLE_COORDINATE_H__
#define __HASHABLE_COORDINATE_H__

#include "Coordinate.h"
#include "IHashable.h"

#define SZ_HASHABLE_COORDINATE_DATA (2)

class HashableCoordinate : public Coordinate, public IHashable
{
    public:
        HashableCoordinate(int x, int y);
        virtual hash_t Hash() override;
        
    private:
        int _hash;
};

#endif // __HASHABLE_COORDINATE_H__