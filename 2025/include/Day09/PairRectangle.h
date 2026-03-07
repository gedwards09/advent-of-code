#ifndef __PAIR_RECTANGLE_H__
#define __PAIR_RECTANGLE_H__

#include "IComparable.h"

class PairRectangle : public IComparable<PairRectangle>
{
    public:
        PairRectangle(int i, int j, long long area);
        virtual int CompareTo(PairRectangle* other) const override;
        int GetIndexI() const;
        int GetIndexJ() const;
        long long GetArea() const;

    private:
        int _i;
        int _j;
        long long _area;

        long long longCompareTo(PairRectangle* other) const;
};

#endif // __PAIR_RECTANGLE_H__