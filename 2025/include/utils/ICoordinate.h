#ifndef __I_COORDINATE_H__
#define __I_COORDINATE_H__

class ICoordinate
{
    public:
        virtual ~ICoordinate() = default;
        virtual int X() = 0;
        virtual int Y() = 0;
};

#endif // __I_COORDINATE_H__