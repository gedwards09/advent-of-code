#include <cstddef>
#include <cassert>
#include <format>
#include <iostream>

#include "IntegerTableau.h"

IntegerTableau::~IntegerTableau()
{
    delete[] this->_ppRow;
    this->_ppRow = NULL;
}

IntegerTableau::IntegerTableau(int numRows, int numCols) : 
        _numRows(numRows), _numCols(numCols), _ppRow(NULL), _pBranchSet(new int[MAX_COLUMNS]())
{
    int szData;
    szData = numCols * numRows;
    int data[szData];

    for (int i = 0; i < szData; i++)
    {
        data[i] = 0;
    }
    this->init_ppRows(numRows, numCols, data);
    this->init_pBranchSet();
}

// prvate
IntegerTableau::IntegerTableau(IntegerTableau* pMat) :
        _numRows(pMat->_numRows), _numCols(pMat->_numCols), 
        _ppRow(new int*[MAX_ROWS]()), _pBranchSet(new int[MAX_COLUMNS]())
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        if (pMat->_ppRow[i] == NULL)
        {
            this->_ppRow[i] = NULL;
        }
        else
        {
            this->_ppRow[i] = new int[MAX_COLUMNS]();
            memcpy(this->_ppRow[i], pMat->_ppRow[i], sizeof(int) * MAX_COLUMNS);
        }
    }

    memcpy(this->_pBranchSet, pMat->_pBranchSet, sizeof(int) * MAX_COLUMNS);
}

IntegerTableau::IntegerTableau(
        int numRows, int numCols, int* pDataArr, int szDataArr
) : _numRows(numRows), _numCols(numCols), _ppRow(new int*[MAX_ROWS]()),
        _pBranchSet(new int[MAX_COLUMNS]())
{
    assert(numRows * numCols <= szDataArr);
    this->init_ppRows(numRows, numCols, pDataArr);
    this->init_pBranchSet();
}

void IntegerTableau::init_ppRows(int numRows, int numCols, int* pDataArr)
{
    int* pRowData;

    for (int i = 0; i < MAX_ROWS; i++)
    {
        if (i < numRows)
        {
            pRowData = new int[MAX_COLUMNS]();
            memcpy(pRowData, &pDataArr[i * numCols], sizeof(int) * numCols);
            for (int j = numCols; j < MAX_COLUMNS; j++)
            {
                pRowData[j] = 0;
            }
        }
        else
        {
            pRowData = NULL;
        }

        this->_ppRow[i] = pRowData;
    }
}

void IntegerTableau::init_pBranchSet()
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        this->_pBranchSet[i] = 0;
    }
}

int IntegerTableau::NumRows() const
{
    return this->_numRows;
}

int IntegerTableau::NumColumns() const
{
    return this->_numCols;
}

int IntegerTableau::Size() const
{
    return this->_numRows * this->_numCols;
}

int IntegerTableau::Element(int rowNum, int colNum) const
{
    return this->_ppRow[rowNum][colNum];
}

int IntegerTableau::IsBranched(int colNum) const
{
    return this->_pBranchSet[colNum];
}

void IntegerTableau::SetBranched(int colNum, int val)
{
    this->_pBranchSet[colNum] = val;
}

void IntegerTableau::RowSwap(int tgtRowNum, int srcRowNum)
{
    int* pTmp;

    pTmp = this->_ppRow[tgtRowNum];
    this->_ppRow[tgtRowNum] = this->_ppRow[srcRowNum];
    this->_ppRow[srcRowNum] = pTmp;
}

void IntegerTableau::RowAdd(int tgtRowNum, int srcRowNum)
{
    this->RowAdd(tgtRowNum, srcRowNum, 1);
}

void IntegerTableau::RowAdd(int tgtRowNum, int srcRowNum, int times)
{
    int* pTgtRow;
    int* pSrcRow;

    pTgtRow = this->_ppRow[tgtRowNum];
    pSrcRow = this->_ppRow[srcRowNum];
    for (int j = 0; j < this->_numCols; j++)
    {
        pTgtRow[j] += times * pSrcRow[j];
    }
}

void IntegerTableau::RowMult(int tgtRowNum, int mult)
{
    int* pRow;

    pRow = this->_ppRow[tgtRowNum];
    for (int j = 0; j < this->_numCols; j++)
    {
        pRow[j] *= mult;
    }
}

void IntegerTableau::RowGCDDivide(int rowNum)
{
    int gcd;
    int* pRowData;
    int cur;

    gcd = 0;
    pRowData = this->_ppRow[rowNum];
    for (int i = 0; i < this->_numCols; i++)
    {
        cur = pRowData[i];
        if (cur == 0)
        {
            continue;
        }

        if (gcd == 0)
        {
            gcd = cur;
        }
        else
        {
            gcd = IntegerTableau::GCD(cur, gcd);
            if (gcd == 1)
            {
                // nothing to do
                return;
            }
        }
    }

    if (gcd > 1)
    {
        for (int i = 0; i < this->_numCols; i++)
        {
            assert(pRowData[i] % gcd == 0);
            pRowData[i] /= gcd;
        }
    }
}

int IntegerTableau::GCD(int a, int b)
{
    int tmp;

    if (a < 0)
    {
        a = -a;
    }

    if (b < 0)
    {
        b = -b;
    }

    if (a < b)
    {
        tmp = b;
        b = a;
        a = tmp;
    }

    if (a == 0)
    {
        return 0;
    }

    while (b != 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

void IntegerTableau::ColumnSwap(int tgtColNum, int srcColNum)
{
    int tmp;
    int* pRow;
    
    for (int rowNum = 0; rowNum < this->_numRows; rowNum++)
    {
        pRow = this->_ppRow[rowNum];
        tmp = pRow[tgtColNum];
        pRow[tgtColNum] = pRow[srcColNum];
        pRow[srcColNum] = tmp;
    }
}

void IntegerTableau::ExtendArtificalColumns(int dataRowNum)
{
    int count;
    int oldNumCols;

    oldNumCols = this->_numCols;
    count = this->_numRows - dataRowNum;
    this->_numCols = oldNumCols + count;
    assert(this->_numCols < MAX_COLUMNS);
    this->ColumnSwap(oldNumCols - 1, this->_numCols - 1);
    for (int i = 0; i < count; i++)
    {
        this->_ppRow[0][oldNumCols + i - 1] = -1;
        this->_ppRow[dataRowNum + i][oldNumCols + i - 1] = 1;
    }
}

void IntegerTableau::RetractColumns(int count)
{
    int rowNum;
    int startColNum;
    int numCols;

    rowNum = 0;
    startColNum = 0;
    this->_ppRow[rowNum][startColNum] = 1;
    startColNum++;
    for (int colNum = startColNum; colNum < this->_numCols; colNum++)
    {
        this->_ppRow[rowNum][colNum] = 0;
    }

    for (numCols = this->_numCols; count > 0; count--, numCols--)
    {
        this->ZeroColumn(numCols - 1);
    }
    this->_numCols = numCols;
}

void IntegerTableau::ZeroColumn(int colNum)
{
    for (int rowNum = 0; rowNum < this->_numRows; rowNum++)
    {
        this->_ppRow[rowNum][colNum] = 0;
    }
}

void IntegerTableau::ZeroRow(int rowNum)
{
    for (int colNum = 0; colNum < this->_numCols; colNum++)
    {
        this->_ppRow[rowNum][colNum] = 0;
    }
}

int* IntegerTableau::GetRow(int rowNum)
{
    assert(0 <= rowNum && rowNum < this->_numRows);
    return this->_ppRow[rowNum];
}

void IntegerTableau::ExtendRowAndColumnDim(int* pRowData, int szRowData)
{
    int newRowNum;
    int* pNewRowData;

    assert(szRowData <= this->_numCols + 1);
    assert(this->_numRows + 1 <= MAX_ROWS);

    newRowNum = this->_numRows;

    if (this->_ppRow[newRowNum] == NULL)
    {
        pNewRowData = new int[MAX_COLUMNS]();
        for (int i = 0; i < MAX_COLUMNS; i++)
        {
            pNewRowData[i] = 0;
        }
        this->_ppRow[newRowNum] = pNewRowData;
    }

    memcpy(this->_ppRow[newRowNum], pRowData, sizeof(int) * szRowData);

    this->_numCols++;
    this->_numRows++;
}

void IntegerTableau::RetractRowAndColumnDim()
{
    int removeColNum;
    int removeRowNum;

    removeColNum = this->_numCols - 1;
    removeRowNum = this->_numCols - 1;
    this->ZeroColumn(removeColNum);
    this->ZeroRow(removeRowNum);

    this->_numCols--;
    this->_numRows--;
}

IntegerTableau* IntegerTableau::Copy()
{
    return new IntegerTableau(this);
}

void IntegerTableau::Print() const
{
    int* pRow;

    for (int i = 0; i < this->_numRows; i++)
    {
        pRow = this->_ppRow[i];

        std::cout << '|';
        for (int j = 0; j < this->_numCols; j++)
        {
            if (j + 1 == this->_numCols)
            {
                std::cout << " |";
            }

            std::cout << std::format("{:>4}", pRow[j]);
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}