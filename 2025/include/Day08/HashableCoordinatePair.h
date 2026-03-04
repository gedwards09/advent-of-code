#ifndef __HASHABLE_COORDINATE_PAIR_H__
#define __HASHABLE_COORDINATE_PAIR_H__

#include "IComparable.h"
#include "HashableCoordinate.h"
#include "Pair.h"

class HashableCoordinatePair : public Pair<HashableCoordinate>, public IComparable<HashableCoordinatePair>
{
    public:
        HashableCoordinatePair(HashableCoordinate* left, HashableCoordinate* right);
        virtual int CompareTo(HashableCoordinatePair* other) const override;
        long long GetSquaredDistance() const;
        void Print() const;

    private:
        long long _dist;

        static long long ConstructSquaredDistance(ICoordinate* left, ICoordinate* right);
};

#endif // __HASHABLE_COORDINATE_PAIR_H__