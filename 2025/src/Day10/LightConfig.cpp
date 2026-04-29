#include <cassert>

#include "HashTable.h"
#include "Queue.h"

#include "LightConfig.h"

LightConfig::~LightConfig()
{
    delete this->_buttonArray;
    this->_buttonArray = NULL;

    for (int i =0; i < MAX_INT_KEY; i++)
    {
        delete this->_hashKeyArray[i];
    }

    for (int i = 0; i < MAX_BUTTON_PRESS; i++)
    {
        delete this->_intArray[i];
    }
}

LightConfig::LightConfig() : 
        _buttonArray(new Array<HashableInteger>())
{
    LightConfig::InitArray((void**)this->_hashKeyArray, MAX_INT_KEY);
    LightConfig::InitArray((void**)this->_intArray, MAX_BUTTON_PRESS);
}

void LightConfig::InitArray(void** ppArr, size_t sz)
{
    for (size_t i = 0; i < sz; i++)
    {
        ppArr[i] = NULL;
    }
}

int LightConfig::SolveAll(std::string contents[], size_t szContents)
{
    int ct;

    ct = 0;
    for (size_t i = 0; i < szContents; i++)
    {
        ct += this->Solve(contents[i]);
    }

    return ct;
}

int LightConfig::Solve(std::string line)
{
    const char* pStr;
    size_t szStr;
    size_t idx;

    pStr = line.c_str();
    szStr = line.length();
    idx = 0;
    this->_target = 0;
    idx = LightConfig::ReadTargetValue(&this->_target, pStr, szStr, idx);
    idx = this->ReadButtonsIntoArray(pStr, szStr, idx);
    idx = this->ReadJoltageIntoArray(pStr, szStr, idx);

    return this->Search();
}

size_t LightConfig::ReadTargetValue(
        int* pTargetValue, const char* pStr, size_t szStr, size_t idx)
{
    int value;
    
    assert(idx < szStr && pStr[idx] == LightConfig::s_startConfig);
    value = 1;
    idx++;
    while (idx < szStr && pStr[idx] != LightConfig::s_endConfig)
    {
        if (pStr[idx] == LightConfig::s_lightOn)
        {
            (*pTargetValue) |= value;
        }
        idx++;
        value <<= 1;
    }

    idx++;
    idx = LightConfig::ReadWhitespace(pStr, szStr, idx);

    return idx;
}

size_t LightConfig::ReadWhitespace(const char* pStr, size_t szStr, size_t idx)
{
    while (idx < szStr && pStr[idx] == LightConfig::s_space)
    {
        idx++;
    }

    return idx;
}

size_t LightConfig::ReadButtonsIntoArray(
        const char* pStr, size_t szStr, size_t idx)
{
    int value;

    this->ClearButtonArray();
    while (idx < szStr && pStr[idx] == LightConfig::s_startButton)
    {
        idx = LightConfig::ReadButton(&value, pStr, szStr, idx);
        this->AppendButtonToArray(value);
    }

    return idx;
}

void LightConfig::ClearButtonArray()
{
    this->_buttonArray->Clear();
}

size_t LightConfig::ReadButton(
        int* pValue, const char* pStr, size_t szStr, size_t idx)
{
    int digit;

    assert(idx < szStr && pStr[idx] == LightConfig::s_startButton);
    *pValue = 0;
    idx++;
    while (idx < szStr && pStr[idx] != LightConfig::s_endButton)
    {
        if (pStr[idx] != LightConfig::s_digitSep)
        {
            digit = pStr[idx] - LightConfig::s_zero;
            assert(0 <= digit && digit <= 9);
            (*pValue) += 1 << digit;
        }

        idx++;
    }

    idx++;
    idx = LightConfig::ReadWhitespace(pStr, szStr, idx);

    return idx;
}

void LightConfig::AppendButtonToArray(uint16_t value)
{
    HashableInteger* pButtonValue;

    pButtonValue = this->getHashableInteger(value);
    this->_buttonArray->Append(pButtonValue);
}

size_t LightConfig::ReadJoltageIntoArray(
        const char* pStr, size_t szStr, size_t idx)
{
    uint8_t value;

    assert(idx < szStr && pStr[idx] == LightConfig::s_startJoltage);
    this->ClearJoltageArray();
    idx++;
    while (idx < szStr && pStr[idx] != LightConfig::s_endJoltage)
    {
        if (pStr[idx] == LightConfig::s_digitSep)
        {
            idx++;
        }
        else
        {
            idx = LightConfig::ReadJoltage(&value, pStr, szStr, idx);
            this->AppendJoltageToArray(value);
        }
    }

    return idx;
}

// do nothing
void LightConfig::ClearJoltageArray() {  }

size_t LightConfig::ReadJoltage(
        uint8_t* pValue, const char* pStr, size_t szStr, size_t idx)
{
    *pValue = 0;
    while (idx < szStr && LightConfig::s_zero <= pStr[idx] 
            && pStr[idx] <= LightConfig::s_nine)
    {
        *pValue *= 10;
        *pValue += (uint8_t)(pStr[idx] - LightConfig::s_zero);
        idx++;
    }

    return idx;
}

// do nothing
void LightConfig::AppendJoltageToArray(uint8_t value)
{
    (void)value;
}

int LightConfig::Search()
{
    return this->bfs(this->_target, this->_buttonArray);
}

int LightConfig::bfs(int target, Array<HashableInteger>* pArray)
{
    HashTable<HashableInteger,int> visited;
    HashTable<HashableInteger,int>* pVisited;
    Queue<HashableInteger> queue;
    Queue<HashableInteger>* pQueue;
    int szArray;
    HashableInteger* pCurrent;
    int* pStepCount;
    int currentValue;
    int currentStepCount;
    int* pValue;
    int newValue;

    pVisited = &visited;
    pQueue = &queue;
    szArray = pArray->Size();

    pCurrent = this->getHashableInteger(START_NUM);
    pStepCount = this->getInt(START_STEPS);
    pVisited->Set(pCurrent, pStepCount);

    pQueue->Enqueue(pCurrent);

    while (!pQueue->IsEmpty())
    {
        pCurrent = pQueue->Dequeue();
        // we should have already visited this node
        assert(pVisited->Get(pCurrent, &pStepCount));
        currentValue = pCurrent->Value;
        currentStepCount = *pStepCount;
        currentStepCount++;
        pStepCount = this->getInt(currentStepCount);
        for (int i = 0; i < szArray; i++)
        {
            pCurrent = this->_buttonArray->Get(i);
            assert(pCurrent != NULL);
            newValue = (pCurrent->Value) ^ currentValue;
            if (newValue == target)
            {
                pVisited->Clear();
                pQueue->Clear();
                this->_buttonArray->Clear();
                return currentStepCount;
            }
            pCurrent = this->getHashableInteger(newValue);
            if (!pVisited->Get(pCurrent, &pValue))
            {
                pVisited->Set(pCurrent, pStepCount);
                pQueue->Enqueue(pCurrent);
            }
        }
    }

    pVisited->Clear();
    pQueue->Clear();
    this->_buttonArray->Clear();
    return pStepCount != NULL ? *pStepCount : 0;
}

HashableInteger* LightConfig::getHashableInteger(int i)
{
    assert(0 <= i && i < MAX_INT_KEY);
    if (this->_hashKeyArray[i] == NULL)
    {
        this->_hashKeyArray[i] = new HashableInteger(i);
    }

    return this->_hashKeyArray[i];
}

int* LightConfig::getInt(int i)
{
    assert(0 <= i && i < MAX_BUTTON_PRESS);
    if (this->_intArray[i] == NULL)
    {
        this->_intArray[i] = new int(i);
    }

    return this->_intArray[i];
}
