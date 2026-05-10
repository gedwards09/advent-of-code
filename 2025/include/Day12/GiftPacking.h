#ifndef __GIFT_PACKING_H__
#define __GIFT_PACKING_H__

#include <string>

#include "Array.h"
#include "CongruenceClass.h"
#include "StringSplitter.h"
#include "TreeConfig.h"

typedef GiftShape shape_t;

typedef CongruenceClass class_t;

typedef TreeConfig config_t;

class GiftPacking
{
    public:
        ~GiftPacking();
        GiftPacking(std::string contents[], size_t szContents);
        int Solve();
        int SolveTreeConfig(config_t* pTreeConfig);

    private:
        static const char s_giftIndicator;
        static const char s_treeConfigDelim;
        static const char s_dimensionDataDelim;
        static const char s_rowColumnDimensionDelim;
        static const int s_rawRowDimensionPiece;
        static const int s_rawColDimensionPiece;

        Array<class_t>* _shapeClasses;
        Array<config_t>* _treeConfigs;

        void ParseContents(std::string contents[], size_t szContents);
        int ParseGiftShape(std::string contents[], size_t lineNumber);
        uint8_t ReadGiftShapeID(std::string line);
        void ReadGiftShapeLineData(std::string line, uint8_t o_data[], int szData);
        void ParseTreeConfig(std::string line);
        int NumClasses() const;
};

#endif // __GIFT_PACKING_H__
