#ifndef __TACH_MAP_H__
#define __TACH_MAP_H__

#include "ITachMap.h"
#include "Map.h"

#define SZ_BYTE (8)
#define LBIT ((unsigned char)0x80)
#define RBIT ((unsigned char)0x01)
#define TACH_MAP_START_LN (0)

typedef unsigned char uint8_t;

class TachMap : public Map, public ITachMap
{
    public:
        virtual ~TachMap();
        TachMap(std::string contents[], size_t szContents);
        virtual long long CountBeamSplits() override;

    protected:
        virtual long long Process();
        virtual int Init();
        virtual bool HasStartIndicator(size_t xCoord);
        virtual bool HasBeam(size_t xCoord);
        virtual long long SplitBeamCount(size_t xCoord);

    private:
        static const char s_carat = '^';
        static const char s_start = 'S';

        const int _szBitmap;
        uint8_t* _pBitmap;

        static int SzBitmap(size_t sz);
        static int CoordToByteNum(size_t i);
        static int CoordToBytePos(size_t i);
        uint8_t readStartByteAt(int byteNum);
        int process(uint8_t* pBitmap);
        static void BitmapSet(uint8_t* pBitmap, size_t xCoord, uint8_t bit);
        static uint8_t BitmapGet(uint8_t* pBitmap, size_t xCoord);
        void bitmapPrint(uint8_t* pBitmap);
        static void BitmapPrint(uint8_t* pBitmap, size_t szBitmap);
};

#endif // __TACH_MAP_H__