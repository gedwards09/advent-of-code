#ifndef __COORDINATE_2D_H__
#define __COORDINATE_2D_H__

#include "ICoordinate.h"

#define XIDX (0)
#define YIDX (1)
#define ZIDX (2)

class Coordinate : public ICoordinate
{
    public:
        Coordinate();
        Coordinate(int x);
        Coordinate(int x, int y);
        Coordinate(int x, int y, int z);
        virtual int X() const override;
        virtual int Y() const override;
        virtual int Z() const override;
        virtual size_t Size() const override;
        virtual int* Serialize(int arr[], size_t sz) const override;
        virtual long long SquaredDistance(ICoordinate* other) const override;
        virtual void Print() const override;
        
    private:
        static const int s_defaultValue = 0;

        const size_t _sz;
        const int _array[MAX_DIM];
        
        /** Private constructor */
        Coordinate(size_t sz, int x, int y, int z);
        int getAtPos(size_t i) const;
};

#endif // __COORDINATE_H__