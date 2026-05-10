#include "GiftPacking.h"

const char GiftPacking::s_giftIndicator = '#';

const char GiftPacking::s_treeConfigDelim = ' ';

const char GiftPacking::s_dimensionDataDelim = ':';

const char GiftPacking::s_rowColumnDimensionDelim = 'x';

const int GiftPacking::s_rawRowDimensionPiece = 1;

const int GiftPacking::s_rawColDimensionPiece = 0;

GiftPacking::~GiftPacking()
{
    delete this->_treeConfigs;
    this->_treeConfigs = NULL;

    delete this->_shapeClasses;
    this->_shapeClasses = NULL;
}

GiftPacking::GiftPacking(std::string contents[], size_t szContents)
{
    this->_shapeClasses = new Array<class_t>();
    this->_treeConfigs = new Array<TreeConfig>();

    this->ParseContents(contents, szContents);
}

void GiftPacking::ParseContents(std::string contents[], size_t szContents)
{
    size_t i = 0;
    while (i < szContents)
    {
        if (contents[i].size() <= GIFT_SHAPE_WIDTH)
        {
            i = this->ParseGiftShape(contents, i);
        }
        else
        {
            this->ParseTreeConfig(contents[i]);
            i++;
        }
    }
}

int GiftPacking::ParseGiftShape(std::string contents[], size_t lineNumber)
{
    uint8_t id;
    uint8_t data[GIFT_SHAPE_HEIGHT][GIFT_SHAPE_WIDTH];
    GiftShape* pShape;
    CongruenceClass* pClass;

    GiftShape::ClearShapeDataArray(data, GIFT_SHAPE_HEIGHT);

    id = this->ReadGiftShapeID(contents[lineNumber]);
    assert(this->_shapeClasses->Size() == id);
    lineNumber++;
    for (int i = 0; i < GIFT_SHAPE_HEIGHT; i++)
    {
        ReadGiftShapeLineData(contents[lineNumber], data[i], GIFT_SHAPE_WIDTH);
        lineNumber++;
    }

    pShape = new GiftShape(data);
    pClass = new CongruenceClass(pShape);
    this->_shapeClasses->Append(pClass);

    // consume empty line
    lineNumber++;
    
    return lineNumber;
}

uint8_t GiftPacking::ReadGiftShapeID(std::string line)
{
    return (uint8_t)(((line.c_str())[0]) - '0');
}

void GiftPacking::ReadGiftShapeLineData(std::string line, uint8_t o_data[], int szData)
{
    const char* p;

    p = line.c_str();
    for (int i = 0; i < szData; i++)
    {
        if (p[i] == GiftPacking::s_giftIndicator)
        {
            o_data[i] = 1;
        }
    }
}

void GiftPacking::ParseTreeConfig(std::string line)
{
    std::vector<std::string> list;
    int szData;
    std::string piece;
    std::vector<std::string> pieces;
    int numCols;
    int numRows;
    uint8_t data[MAX_SHAPES];

    list = StringSplitter::Split(line, GiftPacking::s_treeConfigDelim);
    szData = 0;
    for (size_t i = 0; i < list.size(); i++)
    {
        piece = list[i];
        if (i == 0)
        {
            piece = StringSplitter::Piece(piece, GiftPacking::s_dimensionDataDelim, 0);
            pieces = StringSplitter::Split(piece, GiftPacking::s_rowColumnDimensionDelim);
            numCols = atoi(pieces[GiftPacking::s_rawColDimensionPiece].c_str());
            numRows = atoi(pieces[GiftPacking::s_rawRowDimensionPiece].c_str());
        }
        else
        {
            data[szData] = atoi(piece.c_str());
            szData++;
        }
    }
    
    this->_treeConfigs->Append(new TreeConfig(numRows, numCols, data, szData));
}

int GiftPacking::Solve()
{
    int count;
    TreeConfig* pt;

    count = 0;
    for (int i = 0; i < this->_treeConfigs->Size(); i++)
    {
        pt = this->_treeConfigs->Get(i);
        count += this->SolveTreeConfig(pt);
    }

    return count;
}

int GiftPacking::SolveTreeConfig(TreeConfig* pTreeConfig)
{
    int area;
    int gifts;
    uint8_t* array;
    
    array = pTreeConfig->ShapeCountArray();
    area = pTreeConfig->NumCols() * pTreeConfig->NumRows();
    gifts = 0;
    for (int i = 0; i < pTreeConfig->ShapeCountSize(); i++)
    {
        gifts += array[i] * this->_shapeClasses->Get(i)->Area();
    }
    
    return (gifts < area);
}

int GiftPacking::NumClasses() const
{
    return this->_shapeClasses->Size();
}