#include <cassert>
#include <iostream>

#include "GiftShape.h"

const char GiftShape::s_present = '#';

const char GiftShape::s_absent = '.';

GiftShape::GiftShape(uint8_t array[][GIFT_SHAPE_WIDTH])
{
    memcpy(this->_array, array, sizeof(uint8_t) * GIFT_SHAPE_HEIGHT * GIFT_SHAPE_WIDTH);
    this->_shapeIdent = GiftShape::GenerateShapeIdent(this->_array);
    this->_area = GiftShape::GenerateShapeArea(this->_array);
}

int GiftShape::GenerateShapeIdent(uint8_t array[][GIFT_SHAPE_WIDTH])
{
    int shapeIdent;
    uint8_t value;

    shapeIdent = 0;
    for (int i = 0 ; i < GIFT_SHAPE_HEIGHT; i++)
    {
        for (int j = 0; j < GIFT_SHAPE_WIDTH; j++)
        {
            value = array[i][j];
            shapeIdent <<= 1;
            shapeIdent |= (0x01 & value);
        }
    }

    return shapeIdent;
}

int GiftShape::GenerateShapeArea(uint8_t array[][GIFT_SHAPE_WIDTH])
{
    int area;
    uint8_t value;

    area = 0;
    for (int i = 0 ; i < GIFT_SHAPE_HEIGHT; i++)
    {
        for (int j = 0; j < GIFT_SHAPE_WIDTH; j++)
        {
            value = array[i][j];
            value &= 0x01;
            area += value;
        }
    }

    return area;
}

int GiftShape::ShapeIdent() const
{
    return this->_shapeIdent;
}

uint8_t** GiftShape::ShapeData() const
{
    return (uint8_t**)this->_array;
}

int GiftShape::Area() const
{
    return this->_area;
}

bool GiftShape::IsPresent(int rowIdx, int colIdx) const
{
    if (rowIdx < 0 || GIFT_SHAPE_HEIGHT <= rowIdx || colIdx < 0 || GIFT_SHAPE_WIDTH <= rowIdx)
    {
        assert(false);
    }
    return (this->_array[rowIdx][colIdx] == 1);
}

void GiftShape::ClearShapeDataArray(uint8_t o_data[][GIFT_SHAPE_WIDTH], int szData)
{
    for (int i = 0; i < szData; i++)
    {
        for (int j = 0; j < GIFT_SHAPE_WIDTH; j++)
        {
            o_data[i][j] = 0;
        }
    }
}

void GiftShape::Print() const
{
    for (int i = 0; i < GIFT_SHAPE_HEIGHT; i++)
    {
        for(int j = 0; j < GIFT_SHAPE_WIDTH; j++)
        {
            std::cout << 
                ((this->_array[i][j] == 0)
                    ? GiftShape::s_absent
                    : GiftShape::s_present);
        }

        std::cout << std::endl;
    }
}