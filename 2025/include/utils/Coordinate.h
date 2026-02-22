#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include "ICoordinate.h"

class Coordinate : public ICoordinate
{
    public:
        Coordinate(int x, int y);
        virtual int X() override;
        virtual int Y() override;
        
    private:
        int _x;
        int _y;
};

#endif // __HASHABLE_COORDINATE_H__