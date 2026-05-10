#ifndef __TREE_CONFIG_H__
#define __TREE_CONFIG_H__

#include <cstdint>

#define MAX_SHAPES (8)

class TreeConfig
{
    public:
        TreeConfig(int numRows, int numCols, uint8_t shapeCount[], int szShapeCount);
        int NumRows() const;
        int NumCols() const;
        int ShapeCountSize() const;
        uint8_t* ShapeCountArray() const;

    private:
        int _numRows;
        int _numCols;
        int _szShapeCounts;
        uint8_t _shapeCounts[MAX_SHAPES];
};

#endif // __TREE_CONFIG_H__