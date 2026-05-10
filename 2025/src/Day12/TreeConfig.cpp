#include "TreeConfig.h"

TreeConfig::TreeConfig(int numRows, int numCols, uint8_t shapeCounts[], int szShapeCounts)
    : _numRows(numRows), _numCols(numCols), _szShapeCounts(szShapeCounts)
{
    for (int i = 0; i < MAX_SHAPES; i++)
    {
        if (i < szShapeCounts)
        {
            this->_shapeCounts[i] = shapeCounts[i];
        }
        else
        {
            this->_shapeCounts[i] = 0;
        }
    }
}

int TreeConfig::NumRows() const
{
    return this->_numRows;
}

int TreeConfig::NumCols() const
{
    return this->_numCols;
}

int TreeConfig::ShapeCountSize() const
{
    return this->_szShapeCounts;
}

uint8_t* TreeConfig::ShapeCountArray() const
{
    return (uint8_t*)this->_shapeCounts;
}