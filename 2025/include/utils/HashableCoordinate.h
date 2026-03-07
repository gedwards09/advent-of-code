#ifndef __HASHABLE_COORDINATE_H__
#define __HASHABLE_COORDINATE_H__

#include "Coordinate.h"
#include "IHashable.h"

#define SZ_MAX_ARR (3)

class HashableCoordinate : public Coordinate, public IHashable
{
    public:
        HashableCoordinate();
        HashableCoordinate(int x);
        HashableCoordinate(int x, int y);
        HashableCoordinate(int x, int y, int z);
        virtual hash_t Hash() const override;
        
    private:
        const hash_t _hash;

        static hash_t ConstructHash(ICoordinate* coord);
};

#endif // __HASHABLE_COORDINATE_2D_H__