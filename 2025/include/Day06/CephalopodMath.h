#ifndef __CEPHALOPOD_MATH_H__
#define __CEPHALOPOD_MATH_H__
#include <string>

#include "Array.h"

class CephalopodMath
{
    public:
        CephalopodMath();
        long long ColumnSolve(std::string contents[], size_t szContents);
        static long long CephalopodSolve(std::string contents[], size_t szContents);

    private:
        static const char s_space;
        static const char s_mult;
        static const char s_add;

        Array<Array<int>>* _valueArrays;
        Array<const char>* _operations;
        int _size;

        void clear();
        static Array<int>* ProcessIntegerLine(const char* pLine, size_t szLine);
        static void AppendValueIfPositive(Array<int>* pArr, int current);
        static Array<const char>* ProcessOperationLine(const char* pLine, size_t szLine);
        long long solve();
        static long long CalculateCephalopodOperation(Array<int>* pArr, bool doMultiply);
};

#endif // __CEPHALOPOD_MATH_H__