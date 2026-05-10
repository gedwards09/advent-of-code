#ifndef __GIFT_SHAPE_H__
#define __GIFT_SHAPE_H__
#include <cstdint>

#define GIFT_SHAPE_HEIGHT (3)
#define GIFT_SHAPE_WIDTH (3)

class GiftShape
{
    public:
        GiftShape(uint8_t array[][GIFT_SHAPE_WIDTH]);
        static int GenerateShapeIdent(uint8_t array[][GIFT_SHAPE_WIDTH]);
        static int GenerateShapeArea(uint8_t array[][GIFT_SHAPE_WIDTH]);
        int ShapeIdent() const;
        uint8_t** ShapeData() const;
        int Area() const;
        bool IsPresent(int rowIdx, int colIdx) const;
        static void ClearShapeDataArray(uint8_t array[][GIFT_SHAPE_WIDTH], int szArray);
        void Print() const;

    private:
        static const char s_present;
        static const char s_absent;

        int _shapeIdent;
        uint8_t _array[GIFT_SHAPE_HEIGHT][GIFT_SHAPE_WIDTH];
        int _area;
};

#endif // __GIFT_SHAPE_H__