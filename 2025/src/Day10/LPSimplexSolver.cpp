#include <cassert>

#include "LPSimplexSolver.h"

long long LPSimplexSolver::Solve(IntegerTableau* pMat)
{
    float upperBound;
    bool isIntegral;
    float solution;

    upperBound = -1.0;
    isIntegral = false;
    solution = LPSimplexSolver::SolveILP(pMat, &upperBound, &isIntegral);

    assert(isIntegral);

    return (int)solution;
}

float LPSimplexSolver::SolveILP(IntegerTableau* pMat, float* pUpperBound, bool* pIsIntegral)
{
    int objRowNum;
    float solution;
    int pivotColNum;

    objRowNum = 1;
    solution = LPSimplexSolver::SolveRelaxedLP(pMat);

    if (solution == -1)
    {
        // linear relaxation is infeasible, so integer solution exists
        return -1;
    }

    if (*pUpperBound > 0 && *pUpperBound < solution)
    {
        // no solution smaller than the upper bound exists
        // done with this branch
        return -1; // no solution exists
    }
    
    *pIsIntegral = LPSimplexSolver::IsSolutionIntegral(pMat, objRowNum, &pivotColNum);
    if (*pIsIntegral)
    {
        // this is the optimal integer solution on this branch
        // and so any optimal solution must be no greater than this one
        *pUpperBound = solution;
        // no need to explore sub-branches
        return solution;
    }

    return LPSimplexSolver::ApplyBranchAndBoundMethod(pMat, pivotColNum, objRowNum, pUpperBound, pIsIntegral);
}


float LPSimplexSolver::SolveRelaxedLP(IntegerTableau* pMat)
{
    int numRows;
    int numCols;
    int objRowNum;
    int stopColNum;
    int colNum;
    int element;
    int pivotRow;
    int endColNum;
    int inVarNum;
    int outVarNum;
    int tgtColNum;

    numRows = pMat->NumRows();
    numCols = pMat->NumColumns();

    // Phase I
    objRowNum = 0;
    stopColNum = -1;
    for (colNum = 0; colNum < numCols; colNum++)
    {
        element = pMat->Element(0, colNum);
        if (element < 0)
        {
            if (stopColNum < 0)
            {
                stopColNum = colNum;
            }
            pivotRow = LPSimplexSolver::FindPivotRow(pMat, objRowNum, colNum);

            if (pivotRow < 0)
            {
                continue;
            }

            pMat->RowAdd(objRowNum, pivotRow);
        }
    }

    endColNum = numCols - 1;
    inVarNum = LPSimplexSolver::SelectEnteringVariable(pMat, objRowNum, endColNum);
    while (0 <= inVarNum && inVarNum < numCols)
    {
        outVarNum = LPSimplexSolver::SelectLeavingVariable(pMat, objRowNum, inVarNum);
        LPSimplexSolver::PivotVariable(pMat, inVarNum, outVarNum);

        inVarNum = LPSimplexSolver::SelectEnteringVariable(pMat, objRowNum, endColNum);
    }

    tgtColNum = numCols - 1;
    if (pMat->Element(objRowNum, tgtColNum) != 0)
    {
        // no feasible solution
        return -1;
    }

    // Phase I Cleanup

    for (int inVarNum = stopColNum; inVarNum < numCols - 1; inVarNum++)
    {
        if (pMat->Element(objRowNum, inVarNum) != 0)
        {
            // not in the basis
            continue;
        }

        pivotRow = LPSimplexSolver::FindPivotRow(pMat, objRowNum, inVarNum);
        if (pivotRow < 0)
        {
            continue;
        }

        outVarNum = 0;
        while (pMat->Element(pivotRow, outVarNum) == 0 && outVarNum < stopColNum)
        {
            outVarNum++;
        }

        if (outVarNum < stopColNum)
        {
            pMat->RowMult(pivotRow, -1);
            LPSimplexSolver::PivotVariable(pMat, outVarNum, pivotRow);
        }
    }

    pMat->ColumnSwap(stopColNum, numCols - 1);
    pMat->RetractColumns(numCols - stopColNum - 1);
    numCols = pMat->NumColumns();

    // Phase II
    objRowNum++;
    stopColNum = numCols - 1;
    inVarNum = LPSimplexSolver::SelectEnteringVariable(pMat, objRowNum, stopColNum);
    while (0 <= inVarNum && inVarNum < stopColNum)
    {
        outVarNum = LPSimplexSolver::SelectLeavingVariable(pMat, objRowNum, inVarNum);
        LPSimplexSolver::PivotVariable(pMat, inVarNum, outVarNum);
        inVarNum = LPSimplexSolver::SelectEnteringVariable(pMat, objRowNum, stopColNum);
    }

    for (int i = 0; i < numRows; i++)
    {
        if (pMat->Element(i, numCols - 1) < 0)
        {
            pMat->RowMult(i, -1);
        }
    }

    return LPSimplexSolver::GetMaxObjectiveValue(pMat, objRowNum);
}

int LPSimplexSolver::SelectEnteringVariable(IntegerTableau* pMat, int objRowNum, int endColNum)
{
    int maxElement;
    int pivotColNum;
    int startColNum;
    int element;

    maxElement = -1;
    pivotColNum = -1;
    startColNum = objRowNum + 1;
    for (int colNum = startColNum; colNum < endColNum; colNum++)
    {
        element = pMat->Element(objRowNum, colNum);
        if (element <= 0)
        {
            continue;
        }

        if (maxElement < element)
        {
            maxElement = element;
            pivotColNum = colNum;
        }
    }

    return pivotColNum;
}

int LPSimplexSolver::SelectLeavingVariable(IntegerTableau* pMat, int objRowNum, int colNum)
{
    double minRatio;
    int pivotRowNum;
    int tgtColNum;
    int startRowNum;
    int srcElement;
    int tgtElement;
    double ratio;

    minRatio = -1;
    pivotRowNum = -1;
    tgtColNum = pMat->NumColumns() - 1;
    startRowNum = objRowNum + 1;
    for (int i = startRowNum; i < pMat->NumRows(); i++)
    {
        srcElement = pMat->Element(i, colNum);
        if (srcElement <= 0)
        {
            continue;
        }

        tgtElement = pMat->Element(i, tgtColNum);
        ratio = 1.0 * tgtElement / srcElement;
        if (minRatio == -1 || ratio < minRatio)
        {
            minRatio = ratio;
            pivotRowNum = i;
        }
    }

    return pivotRowNum;
}

void LPSimplexSolver::PivotVariable(IntegerTableau* pMat, int colNum, int pivotRow)
{
    int numRows;
    int pivotElement;
    int rowNum;
    int element;
    int gcd;

    numRows = pMat->NumRows();
    pivotElement = pMat->Element(pivotRow, colNum);
    for (rowNum = 0; rowNum < numRows; rowNum++)
    {
        if (rowNum == pivotRow)
        {
            continue;
        }

        element = pMat->Element(rowNum, colNum);
        if (element == 0)
        {
            continue;
        }

        gcd = IntegerTableau::GCD(element, pivotElement);
        pMat->RowMult(rowNum, pivotElement / gcd);
        pMat->RowAdd(rowNum, pivotRow, -(element/gcd));
        pMat->RowGCDDivide(rowNum);
    }
}

float LPSimplexSolver::ApplyBranchAndBoundMethod(
        IntegerTableau* pMat, int pivotColNum, int objRowNum, float* pUpperBound, bool* pIsIntegral)
{
    int pivotRowNum;
    int tgtColNum;
    int pivotElement;
    int tgtElement;
    int quot;
    IntegerTableau* pMatCopy;
    int dir;
    int floor;
    float floorSolution;
    bool isFloorIntegral;
    int ceil;
    float ceilSolution;
    bool isCeilIntegral;

    pivotRowNum = LPSimplexSolver::FindPivotRow(pMat, objRowNum, pivotColNum);

    tgtColNum = pMat->NumColumns() - 1;
    pivotElement = pMat->Element(pivotRowNum, pivotColNum);
    tgtElement = pMat->Element(pivotRowNum, tgtColNum);
    assert(tgtElement % pivotElement != 0);

    quot = (int)tgtElement / pivotElement;
    if ((tgtElement > 0) != (pivotElement > 0))
    {
        quot--;
    }

    pMat->SetBranched(pivotColNum, true);
    pMatCopy = pMat->Copy();

    dir = 1;
    floor = quot;
    isFloorIntegral = false;
    LPSimplexSolver::ExtendTableau(pMat, pivotColNum, dir, floor);
    floorSolution = LPSimplexSolver::SolveILP(pMat, pUpperBound, &isFloorIntegral);

    dir = -1;
    ceil = quot + 1;
    isCeilIntegral = false;
    LPSimplexSolver::ExtendTableau(pMatCopy, pivotColNum, dir, ceil);
    ceilSolution = LPSimplexSolver::SolveILP(pMatCopy, pUpperBound, &isCeilIntegral);

    delete pMatCopy;

    *pIsIntegral = isFloorIntegral || isCeilIntegral;
    if (isFloorIntegral)
    {
        return (!isCeilIntegral || floorSolution < ceilSolution) ? floorSolution : ceilSolution;
    }
    else if (isCeilIntegral)
    {
        return ceilSolution;
    }
    else
    {
        // no solution for this branch
        return -1;
    }
}

bool LPSimplexSolver::IsSolutionIntegral(IntegerTableau* pMat, int objRowNum, int* pPivotColNum)
{
    bool isSolutionIntegral;
    int startColNum;
    int tgtColNum;
    int pivotColNum;
    float maxRatio;
    int element;
    int pivotRowNum;
    int pivotElement;
    int tgtElement;
    float ratio;

    isSolutionIntegral = true;
    startColNum = objRowNum + 1;
    tgtColNum = pMat->NumColumns() - 1;
    pivotColNum = -1;
    maxRatio = 0;

    for (int colNum = startColNum; colNum < tgtColNum; colNum++)
    {
        element = pMat->Element(objRowNum, colNum);
        assert(element <= 0);

        // not a basic varable
        if (element < 0)
        {
            continue;
        }

        pivotRowNum = LPSimplexSolver::FindPivotRow(pMat, objRowNum, colNum);

        if (pivotRowNum < 0)
        {
            continue;
        }

        pivotElement = pMat->Element(pivotRowNum, colNum);
        tgtElement = pMat->Element(pivotRowNum, tgtColNum);

        if (tgtElement % pivotElement != 0)
        {
            isSolutionIntegral = false;

            ratio = 1.0 * (tgtElement % pivotElement) / pivotElement;

            if (ratio < 0)
            {
                ratio = -1 * ratio;
            }

            if (ratio > 0.50)
            {
                ratio = 1 - ratio;
            }

            if (maxRatio < ratio && !pMat->IsBranched(colNum))
            {
                pivotColNum = colNum;
                maxRatio = ratio;
            }
        }
    }

    *pPivotColNum = pivotColNum;

    return isSolutionIntegral;
}

int LPSimplexSolver::FindPivotRow(IntegerTableau* pMat, int objRowNum, int colNum)
{
    int numRows;
    int startRowNum;
    int pivotRowNum;
    int rowNum;
    int element;

    numRows = pMat->NumRows();
    startRowNum = objRowNum + 1;
    pivotRowNum = -1;
    for (rowNum = startRowNum; rowNum < numRows; rowNum++)
    {
        element = pMat->Element(rowNum, colNum);
        if (element == 0)
        {
            continue;
        }

        if (pivotRowNum < 0)
        {
            pivotRowNum = rowNum;
        }
        else
        {
            pivotRowNum = -1;
            break;
        }
    }

    return pivotRowNum;
}

void LPSimplexSolver::ExtendTableau(IntegerTableau* pMat, int colNum, int dir, int tgtElement)
{
    int szRow = pMat->NumColumns();
    int data[MAX_COLUMNS];
    int dataRowNum;

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (i == colNum)
        {
            data[i] = 1;
        }
        else if (i == szRow - 1)
        {
            // target element into the target column
            data[szRow - 1] = (long long)tgtElement;
        }
        else if (i == szRow)
        {
            // new slack variable goes in the final column
            data[szRow] = (long long)dir;
        }
        else 
        {
            data[i] = 0;
        }
    }

    pMat->ExtendRowAndColumnDim(data, szRow + 1);

    //swap the target column with our slack variable column
    pMat->ColumnSwap(szRow - 1, szRow);

    // create atrifical slack variable columns
    dataRowNum = 2;
    pMat->ExtendArtificalColumns(dataRowNum);
}

float LPSimplexSolver::GetMaxObjectiveValue(IntegerTableau* pMat, int objRowNum)
{
    int numCols;
    int tgtColNum;
    int tgtElement;
    int tgtDenom;

    LPSimplexSolver::ValidateSolution(pMat, objRowNum);

    numCols = pMat->NumColumns();
    tgtColNum = numCols - 1;
    tgtElement = pMat->Element(objRowNum, tgtColNum);
    tgtDenom = pMat->Element(objRowNum, objRowNum);

    return 1.0 * tgtElement / tgtDenom;
}

void LPSimplexSolver::ValidateSolution(IntegerTableau* pMat, int objRowNum)
{
    int numCols;
    int startColNum;
    int tgtColNum;
    int element;

    numCols = pMat->NumColumns();
    startColNum = objRowNum + 1;
    tgtColNum = numCols - 1;
    for (int colNum = startColNum; colNum < tgtColNum; colNum++)
    {
        element = pMat->Element(objRowNum, colNum);
        assert(element <= 0);
    }
}