#ifndef __MAP_H__
#define __MAP_H__

#include <string>

#include "IMap.h"

class Map : public IMap
{
    public:
        Map(std::string contents[], size_t szContents);
        size_t GetSizeX() override;
        size_t GetSizeY() override;
        char GetCoord(int i, int j) override;
        bool IsValidXCoord(int xCoord) override;
        bool IsValidYCoord(int yCoord) override;

    private:
        const std::string* _pContents;
        const size_t _szX;
        const size_t _szY;
        static const char s_nullChar = '\0';

        static size_t createSzX(std::string contents[], size_t szContents);
        static size_t createSzY(size_t szContents);
        bool isValidCoord(int coord, size_t bound);
};

#endif // __MAP_H__