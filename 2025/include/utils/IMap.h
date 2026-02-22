#ifndef __I_MAP_H__
#define __I_MAP_H__

class IMap
{
    public:
        virtual ~IMap() = default;
        virtual size_t GetSizeX() = 0;
        virtual size_t GetSizeY() = 0;
        virtual char GetCoord(int i, int j) = 0;
        virtual bool IsValidXCoord(int xCoord) = 0;
        virtual bool IsValidYCoord(int yCoord) = 0;
};

#endif // __I_MAP_H__