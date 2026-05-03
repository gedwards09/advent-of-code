#ifndef __LP_SIMPLEX_SOLVER_H__
#define __LP_SIMPLEX_SOLVER_H__

#include "IntegerTableau.h"

class LPSimplexSolver
{
    public:
        static long long Solve(IntegerTableau* pMat);
        static float SolveILP(IntegerTableau* pMat, float* pUpperBound, bool* pIsIntegral);
        static float SolveRelaxedLP(IntegerTableau* pMat);
        static bool SolveRelaxedLPPhaseI(IntegerTableau* pMat);
        static void SolveRelaxedLPPhaseII(IntegerTableau* pMat);
        static int SelectEnteringVariable(IntegerTableau* pMat, int objRowNum, int endColNum);
        static int SelectLeavingVariable(IntegerTableau* pMat, int objRowNum, int colNum);
        static void PivotVariable(IntegerTableau* pMat, int colNum, int pivotRow);
        static float ApplyBranchAndBoundMethod(
            IntegerTableau* pMat, int pivotColNum, int objRowNum, float* pLowerBound, bool* pIsIntegral);
        static bool IsSolutionIntegral(IntegerTableau* pMat, int objRowNum, int* pPivotColNum);
        static int FindPivotRow(IntegerTableau* pMat, int objRowNum, int colNum);
        static void ExtendTableau(IntegerTableau* pmat, int colNum, int dir, int tgtElement);
        static float GetMaxObjectiveValue(IntegerTableau* pMat, int objRowNum);
        static void ValidateSolution(IntegerTableau* pMat, int objRowNum);
};

#endif // __LP_SIMPLEX_SOLVER_H__