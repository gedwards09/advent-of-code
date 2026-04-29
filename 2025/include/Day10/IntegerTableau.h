#ifndef __INTEGER_MATRIX_H__
#define __INTEGER_MATRIX_H__

#define MAX_COLUMNS (1024)
#define MAX_ROWS (1024)

class IntegerTableau
{
    public:
        ~IntegerTableau();
        IntegerTableau(int numRows, int numCols);
        IntegerTableau(int numRows, int numCols, int* pDataArr, int szDataArr);
        int NumRows() const;
        int NumColumns() const;
        int Size() const;
        int Element(int rowNum, int colNum) const;
        int IsBranched(int colNum) const;
        void SetBranched(int colNum, int val);
        void RowSwap(int tgtRowNum, int srcRowNum);
        void RowAdd(int tgtRowNum, int srcRowNum);
        void RowAdd(int tgtRowNum, int srcRowNum, int times);
        void RowMult(int tgtRowNum, int mult);
        void RowGCDDivide(int rowNum);
        static int GCD(int a, int b);
        void ColumnSwap(int tgtColNum, int srcColNum);
        void ExtendArtificalColumns(int dataRowNum);
        void RetractColumns(int count);
        void ZeroColumn(int colNum);
        void ZeroRow(int rowNum);
        int* GetRow(int rowNum);
        void ExtendRowAndColumnDim(int* pRowData, int szRowData);
        void RetractRowAndColumnDim();
        IntegerTableau* Copy();
        void Print() const;

    private:
        int _numRows;
        int _numCols;
        int** _ppRow;
        int* _pBranchSet;

        IntegerTableau(IntegerTableau* pmat);
        void init_ppRows(int numRows, int numCols, int* pDataArr);
        void init_pBranchSet();
};

#endif // __INTEGER_MATRIX_H__