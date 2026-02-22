#include <cassert>

#include "IMap.h"
#include "Map.h"

Map::Map(std::string contents[], size_t szContents) : 
        _pContents(contents), 
        _szX(Map::createSzX(contents, szContents)), 
        _szY(Map::createSzY(szContents))
{
    for (size_t i = 0; i < szContents; i++)
    {
        assert(contents[i].length() == this->_szX);
    }
}

size_t Map::createSzX(std::string contents[], size_t szContents)
{
    if (szContents == 0)
    {
        return 0;
    }

    return contents[0].length();
}

size_t Map::createSzY(size_t szContents)
{
    return szContents;
}

size_t Map::GetSizeX()
{
    return this->_szX;
}

size_t Map::GetSizeY()
{
    return this->_szY;
}

char Map::GetCoord(int xCoord, int yCoord)
{
    if (!this->IsValidXCoord(xCoord) || !this->IsValidYCoord(yCoord))
    {
        // we don't throw an error, we just return a null value which will 
        // never appear in a char string
        return Map::s_nullChar;
    }

    return this->_pContents[yCoord][xCoord];
}

bool Map::IsValidXCoord(int xCoord)
{
    return Map::isValidCoord(xCoord, this->_szX);
}

bool Map::IsValidYCoord(int yCoord)
{
    return Map::isValidCoord(yCoord, this->_szY);
}

bool Map::isValidCoord(int coord, size_t bound)
{
    return 0 <= coord && (size_t)coord < bound;
}