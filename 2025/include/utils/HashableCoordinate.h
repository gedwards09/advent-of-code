#ifndef __HASHABLE_COORDINATE_H__
#define __HASHABLE_COORDINATE_H__

#include "IHashableCoordinate.h"

#define SZ_MAX_ARR (2)

class HashableCoordinate : public IHashableCoordinate
{
    public:
        virtual ~HashableCoordinate() override;
        HashableCoordinate(ICoordinate* coord);
        virtual int X() const override;
        virtual int Y() const override;
        virtual int Z() const override;
        virtual size_t Size() const override;
        virtual int* Serialize(int arr[], size_t sz) const override;
        virtual long long SquaredDistance(ICoordinate* other) const override;
        virtual void Print() const override;
        virtual hash_t Hash() const override;
        
    private:
        const ICoordinate* _coord;
        const hash_t _hash;

        static hash_t ConstructHash(ICoordinate* coord);
};

#endif // __HASHABLE_COORDINATE_2D_H__