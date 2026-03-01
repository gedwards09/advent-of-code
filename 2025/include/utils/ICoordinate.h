#ifndef __I_COORDINATE_H__
#define __I_COORDINATE_H__

#define MAX_DIM (3)

class ICoordinate
{
    public:
        virtual ~ICoordinate() = default;
        virtual int X() const = 0;
        virtual int Y() const = 0;
        virtual int Z() const = 0;
        virtual size_t Size() const = 0;
        virtual int* Serialize(int arr[], size_t sz) const = 0;
        virtual long long SquaredDistance(ICoordinate* other) const = 0;
        virtual void Print() const = 0;
};

#endif // __I_COORDINATE_H__