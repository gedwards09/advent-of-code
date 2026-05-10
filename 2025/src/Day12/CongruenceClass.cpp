#include <cstring>
#include <iostream>

#include "CongruenceClass.h"

const int CongruenceClass::s_firstIdx = 0;

CongruenceClass::CongruenceClass(GiftShape* pShape) : 
    _szMembers(0), _members(NULL), _area(0)
{
    this->_members = CongruenceClass::GenerateCongruentShapes(pShape);
    this->_szMembers = this->_members->Size();
    this->_area = pShape->Area();
}

Array<shape_t>* CongruenceClass::GenerateCongruentShapes(GiftShape* pShape)
{
    uint8_t data[GIFT_SHAPE_HEIGHT][GIFT_SHAPE_WIDTH];
    int shapeIdents[DIHEDRAL_GROUP_ORDER];
    Array<shape_t>* pShapes;
    int szShapeIdents;
    int shapeIdent;

    pShapes = new Array<shape_t>();
    szShapeIdents = 0;
    for (int i = 0; i < DIHEDRAL_GROUP_ORDER; i++)
    {
        shapeIdents[i] = 0;
    }

    shape_t::ClearShapeDataArray(data, GIFT_SHAPE_HEIGHT);
    memcpy(data, pShape->ShapeData(), sizeof(uint8_t) * GIFT_SHAPE_HEIGHT * GIFT_SHAPE_WIDTH);

    shapeIdents[szShapeIdents] = pShape->ShapeIdent();
    szShapeIdents++;
    pShapes->Append(pShape);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < ROT_ELEM_ORDER - 1; j++)
        {
            CongruenceClass::RotateData(data);
            shapeIdent = shape_t::GenerateShapeIdent(data);
            if (CongruenceClass::IdentIsInArray(shapeIdent, shapeIdents, szShapeIdents))
            {
                break;
            }

            shapeIdents[szShapeIdents] = shapeIdent;
            szShapeIdents++;
            pShapes->Append(new shape_t(data));
        }

        if (i == 0)
        {
            CongruenceClass::FlipData(data);
            shapeIdent = shape_t::GenerateShapeIdent(data);
            if (CongruenceClass::IdentIsInArray(shapeIdent, shapeIdents, szShapeIdents))
            {
                break;
            }

            shapeIdents[szShapeIdents] = shapeIdent;
            szShapeIdents++;
            pShapes->Append(new shape_t(data));
        }
    }

    return pShapes;
}

void CongruenceClass::RotateData(uint8_t o_data[][GIFT_SHAPE_WIDTH])
{
    int rowIdx;
    int colIdx;
    int tmpVal;
    int tmpIdx;
    int nextVal;

    for (colIdx = 0; colIdx < ((GIFT_SHAPE_WIDTH + 1) / 2); colIdx++)
    {
        rowIdx = 0;
        tmpVal = o_data[rowIdx][colIdx];
        for (int i = 0; i < ROT_ELEM_ORDER; i++)
        {
            // rotate coords
            tmpIdx = rowIdx;
            rowIdx = GIFT_SHAPE_WIDTH - colIdx - 1;
            colIdx = tmpIdx;

            // swap in the value
            nextVal = o_data[rowIdx][colIdx];
            o_data[rowIdx][colIdx] = tmpVal;
            tmpVal = nextVal;
        }
    }
}

void CongruenceClass::FlipData(uint8_t o_data[][GIFT_SHAPE_WIDTH])
{
    int srcColIdx;
    int tgtColIdx;
    int rowIdx;
    int tmpVal;

    srcColIdx = 0;
    tgtColIdx = GIFT_SHAPE_WIDTH - 1;
    for (rowIdx = 0; rowIdx < GIFT_SHAPE_HEIGHT; rowIdx++)
    {
        tmpVal = o_data[rowIdx][srcColIdx];
        o_data[rowIdx][srcColIdx] = o_data[rowIdx][tgtColIdx];
        o_data[rowIdx][tgtColIdx] = tmpVal;
    }
}

bool CongruenceClass::IdentIsInArray(int shapeIdent, int* pArray, int szArray)
{
    while (szArray > 0)
    {
        if (shapeIdent == *pArray)
        {
            return true;
        }

        pArray++;
        szArray--;
    }

    return false;
}

int CongruenceClass::Size() const
{
    return this->_szMembers;
}

int CongruenceClass::Area() const
{
    return this->_area;
}

GiftShape* CongruenceClass::Get(int i) const
{
    if (i < 0 || this->_szMembers <= i)
    {
        assert(false);
    }

    return this->_members->Get(i);
}

int CongruenceClass::First() const
{
    return CongruenceClass::s_firstIdx;
}

bool CongruenceClass::HasNext(int i) const
{
    return (i + 1 < this->_szMembers);
}

int CongruenceClass::Next(int i) const
{
    return ((this->HasNext(i)) ? i + 1 : 0);
}

void CongruenceClass::Print() const
{
    GiftShape* pShape;

    for (int i = 0; i < this->_members->Size(); i++)
    {
        std::cout << i << ':' << std::endl;
        pShape = this->_members->Get(i);
        pShape->Print();
        std::cout << std::endl;
    }
}