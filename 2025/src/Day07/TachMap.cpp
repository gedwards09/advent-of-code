#include <cassert>
#include <iostream>

#include "TachMap.h"

TachMap::~TachMap()
{
    free(this->_pBitmap);
    this->_pBitmap = NULL;
}

TachMap::TachMap(std::string contents[], size_t szContents) : 
        Map(contents, szContents), 
        _szBitmap(TachMap::SzBitmap(this->GetSizeX())),
        _pBitmap(NULL)
{
    this->_pBitmap = (uint8_t*)malloc(sizeof(uint8_t) * this->_szBitmap);
    assert(this->_pBitmap != NULL);
}

int TachMap::SzBitmap(size_t sz)
{
    return (sz + SZ_BYTE - 1) / SZ_BYTE;
}

int TachMap::CoordToByteNum(size_t i)
{
    return i / SZ_BYTE; 
}

int TachMap::CoordToBytePos(size_t i)
{
    return SZ_BYTE - 1 - (i % SZ_BYTE);
}

long long TachMap::CountBeamSplits()
{
    return this->Process();
}

long long TachMap::Process()
{
    long long count;

    count = this->Init();
    for (size_t yCoord = 0; yCoord < this->GetSizeY(); yCoord++)
    {
        if (yCoord == TACH_MAP_START_LN || yCoord % 2 == 1)
        {
            // do nothing
            continue;
        }

        for (size_t xCoord = 0; xCoord < this->GetSizeX(); xCoord++)
        {
            if (this->HasBeam(xCoord)
                    && this->GetCoord(xCoord, yCoord) == TachMap::s_carat)
            {
                count += this->SplitBeamCount(xCoord);
            }
        }
    }

    return count;
}

int TachMap::Init()
{
    for (int i = 0; i < this->_szBitmap; i++)
    {
        *(this->_pBitmap + i) = this->readStartByteAt(i);
    }

    // the initial number of splits (0)
    return 0;
}

uint8_t TachMap::readStartByteAt(int byteNum)
{
    uint8_t bit;
    uint8_t out;

    bit = LBIT;
    out = 0;
    for (int i = 0; i < SZ_BYTE; i++)
    {
        if (this->HasStartIndicator(SZ_BYTE * byteNum + i))
        {
            out |= (bit >> i);
        }
    }

    return out;
}

bool TachMap::HasStartIndicator(size_t xCoord)
{
    return this->GetCoord(xCoord, TACH_MAP_START_LN) == TachMap::s_start;
}

bool TachMap::HasBeam(size_t xCoord)
{
    return TachMap::BitmapGet(this->_pBitmap, xCoord) == RBIT;
}

uint8_t TachMap::BitmapGet(uint8_t* pBitmap, size_t xCoord)
{
    int idx;
    int shift;
    uint8_t byte;

    idx = TachMap::CoordToByteNum(xCoord);
    shift = TachMap::CoordToBytePos(xCoord);
    byte = pBitmap[idx];
    return RBIT & (byte >> shift);    
}

long long TachMap::SplitBeamCount(size_t xCoord)
{
    TachMap::BitmapSet(this->_pBitmap, xCoord - 1, RBIT);
    TachMap::BitmapSet(this->_pBitmap, xCoord, 0);
    TachMap::BitmapSet(this->_pBitmap, xCoord + 1, RBIT);

    return RBIT; // 1
}

void TachMap::BitmapSet(uint8_t* pBitmap, size_t xCoord, uint8_t bit)
{
    int idx;
    int shift;

    idx = TachMap::CoordToByteNum(xCoord);
    shift = TachMap::CoordToBytePos(xCoord);
    if ((bit & RBIT) == RBIT)
    {
        pBitmap[idx] |= (RBIT << shift);
    }
    else
    {
        pBitmap[idx] &= (~(RBIT << shift));
    }
}

void TachMap::bitmapPrint(uint8_t* pBitMap)
{
    TachMap::BitmapPrint(pBitMap, this->_szBitmap);
}

void TachMap::BitmapPrint(uint8_t* pBitmap, size_t szBitmap)
{
    for (size_t byteNum = 0; byteNum < szBitmap; byteNum++)
    {
        std::cout << '.' << std::hex << (int)pBitmap[byteNum];
    }
    std::cout << std::endl;
}