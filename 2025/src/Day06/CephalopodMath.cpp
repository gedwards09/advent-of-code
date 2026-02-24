#include <cassert>
#include <iostream>

#include "DigitString.h"

#include "CephalopodMath.h"

const char CephalopodMath::s_space = ' ';
const char CephalopodMath::s_mult = '*';
const char CephalopodMath::s_add = '+';

void CephalopodMath::clear()
{
    Array<int>* pArr;

    for (int i = 0; i < this->_valueArrays->Size(); i++)
    {
        pArr = this->_valueArrays->Get(i);
        pArr->DeleteAllAndClear();
    }
    this->_valueArrays->DeleteAllAndClear();
    this->_operations->Clear();
}

CephalopodMath::CephalopodMath() : 
        _valueArrays(new Array<Array<int>>), _operations(NULL) {  }

long long CephalopodMath::ColumnSolve(std::string contents[], size_t szContents)
{
    const char* pLine;
    size_t szLine;
    long long out;

    for (size_t i = 0; i < szContents; i++)
    {
        pLine = contents[i].c_str();
        szLine = contents[i].size();
        if (i + 1 == szContents)
        {
            this->_operations = CephalopodMath::ProcessOperationLine(pLine, szLine);
            this->_size = this->_operations->Size();
            for (int j = 0; j < this->_valueArrays->Size(); j++)
            {
                assert(this->_valueArrays->Get(j)->Size() == this->_size);
            }
        }
        else
        {
            this->_valueArrays->Append(CephalopodMath::ProcessIntegerLine(pLine, szLine));
        }
    }

    out =  this->solve();
    this->clear();
    return out;
}

Array<const char>* CephalopodMath::ProcessOperationLine(const char* pLine, size_t szLine)
{
    Array<const char>* pArr;

    pArr = new Array<const char>();
    for (size_t pos = 0; pos < szLine; pos++)
    {
        switch (pLine[pos])
        {
            case CephalopodMath::s_space:
                continue;
                break;
            case CephalopodMath::s_mult:
                pArr->Append(&CephalopodMath::s_mult);
                break;
            case CephalopodMath::s_add:
                pArr->Append(&CephalopodMath::s_add);
                break;
            default:
                // unreachable
                assert(false);
        }
    }

    return pArr;
}

Array<int>* CephalopodMath::ProcessIntegerLine(const char* pLine, size_t szLine)
{
    Array<int>* pArr;
    int current;

    pArr = new Array<int>();
    current = 0;
    for (size_t pos = 0; pos < szLine; pos++)
    {
        if (pLine[pos] == CephalopodMath::s_space)
        {
            CephalopodMath::AppendValueIfPositive(pArr, current);
            current = 0;
            continue;
        }
        else
        {
            current *= BASE10;
            current += DigitString::DigitValue(pLine[pos]);
        }

    }

    CephalopodMath::AppendValueIfPositive(pArr, current);
    return pArr;
}

void CephalopodMath::AppendValueIfPositive(Array<int>* pArr, int current)
{
    if (current > 0)
    {
        pArr->Append(new int(current));
    }
}

long long CephalopodMath::solve()
{
    Array<int>* pArr;
    bool doMultiply;
    long long count;
    long long current;

    count = 0;
    for (int i = 0; i < this->_size; i++)
    {
        doMultiply = (this->_operations->Get(i) == &CephalopodMath::s_mult);
        current = doMultiply ? 1 : 0;
        for (int j = 0; j < this->_valueArrays->Size(); j++)
        {
            pArr = this->_valueArrays->Get(j);
            if (doMultiply)
            {
                current *= (*pArr->Get(i));
            }
            else
            {
                current += (*pArr->Get(i));
            }
        }
        count += current;
    }

    return count;
}

long long CephalopodMath::CephalopodSolve(std::string contents[], size_t szContents)
{
    Array<int> arr;
    Array<int>* pArr;
    size_t szLine;
    long long out;
    int current = 0;
    bool doMultiply;
    char c;

    pArr = &arr;
    szLine = contents[0].size();
    doMultiply = false;
    out = 0;

    for (size_t i = 0; i < szLine; i++)
    {
        doMultiply = doMultiply || (contents[szContents-1][i] == CephalopodMath::s_mult);
        current = 0;
        for (size_t j = 0; j < szContents - 1; j++)
        {
            c = contents[j][i];
            if (c != CephalopodMath::s_space)
            {
                current *= BASE10;
                current += DigitString::DigitValue(c);
            }
        }
        if (current == 0)
        {
            out += CephalopodMath::CalculateCephalopodOperation(pArr, doMultiply);
            pArr->DeleteAllAndClear();
            doMultiply = false;
        }
        else
        {
            pArr->Append(new int(current));
        }
    }
    
    out += CephalopodMath::CalculateCephalopodOperation(pArr, doMultiply);
    pArr->DeleteAllAndClear();
    
    return out;
}

long long CephalopodMath::CalculateCephalopodOperation(Array<int>* pArr, bool doMultiply)
{
    long long out;
    int current;

    out = doMultiply ? 1 : 0;
    for (int i = 0; i < pArr->Size(); i++)
    {
        current = *(pArr->Get(i));
        if (doMultiply)
        {
            out *= current;
        }
        else
        {
            out += current;
        }
    }

    return out;
}