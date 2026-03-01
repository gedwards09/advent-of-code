#ifndef __HASHABLE_COORDINATE_PAIR_H__
#define __HASHABLE_COORDINATE_PAIR_H__

#include "IComparable.h"
#include "IHashableCoordinate.h"
#include "Pair.h"

class HashableCoordinatePair : public Pair<IHashableCoordinate>, public IComparable<HashableCoordinatePair>
{
    public:
        HashableCoordinatePair(IHashableCoordinate* left, IHashableCoordinate* right);
        virtual int CompareTo(HashableCoordinatePair* other) override;
        long long GetSquaredDistance() const;
        void Print() const;

    private:
        long long _dist;

        static long long ConstructSquaredDistance(ICoordinate* left, ICoordinate* right);
};

#endif // __HASHABLE_COORDINATE_PAIR_H__