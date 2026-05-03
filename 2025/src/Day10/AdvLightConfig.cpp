
#include <cassert>

#include "Array.h"
#include "LPSimplexSolver.h"

#include "AdvLightConfig.h"

AdvLightConfig::~AdvLightConfig()
{
    for (int i = 0; i < ADV_MAX_STEPS; i++)
    {
        delete this->_intArray[i];
    }
}

AdvLightConfig::AdvLightConfig()
{
    this->initButtonArray();
    LightConfig::InitArray((void**)this->_intArray, ADV_MAX_STEPS);
    this->initJoltageArray();
}

void AdvLightConfig::initButtonArray()
{
    this->_szButtonArray = 0;

    for (int i = 0; i < MAX_BUTTON_COUNT; i++)
    {
        this->_buttonArray[i] = 0;
    }
}

void AdvLightConfig::initJoltageArray()
{
    this->_szJoltageArray = 0;

    for (int i = 0; i < SZ_JOLTAGE_ARR; i++)
    {
        this->_joltageArray[i] = 0;
    }
}

void AdvLightConfig::ClearButtonArray()
{
    this->initButtonArray();
}

void AdvLightConfig::AppendButtonToArray(uint16_t value)
{
    int count = 0;

    this->_buttonArray[this->_szButtonArray] = value;
    this->_szButtonArray++;

    count = 0;
    while (value != 0)
    {
        if ((value & 0x01) == 0x01)
        {
            count++;
        }
        value >>= 1;
    }

    if (count > this->_maxButtonLen)
    {
        this->_maxButtonLen = count;
    }
}

void AdvLightConfig::ClearJoltageArray()
{
    this->initJoltageArray();
}

void AdvLightConfig::AppendJoltageToArray(uint8_t value)
{
    this->_joltageArray[this->_szJoltageArray] = value;
    this->_szJoltageArray++;
}

int AdvLightConfig::Search()
{
    IntegerTableau* pMat;
    int outVal;

    pMat = this->ConstructMatrix();

    outVal = LPSimplexSolver::Solve(pMat);
    
    delete pMat;

    return outVal;
}

IntegerTableau* AdvLightConfig::ConstructMatrix()
{
    int numButtons;
    int numConstraints;
    int numRow;
    int numCol;
    int szDataArr;
    int* pDataArr;
    int idxRowNum;
    int idxColNum;
    uint16_t button;

    numButtons = this->_szButtonArray;
    numConstraints = this->_szJoltageArray;
    numRow = numConstraints + 2;
    numCol = numButtons + 3;
    szDataArr = numRow * numCol;
    pDataArr = new int[szDataArr];
    
    for (idxColNum = 0; idxColNum < numCol - 1; idxColNum++)
    {
        // 1st row: dummy variable objective
        // W coefficient only; artificial columns added later
        idxRowNum = 0;
        if (idxColNum == 0)
        {
            pDataArr[idxRowNum * numCol + idxColNum] = 1;
        }
        else
        {
            pDataArr[idxRowNum * numCol + idxColNum] = 0;
        }
        
        // 2nd row: Objective Equation
        // total = a_1 + ... + a_n
        idxRowNum++;
        if (idxColNum == 1)
        {
            pDataArr[idxRowNum * numCol + idxColNum] = 1;
        }
        else if (2 <= idxColNum && idxColNum < numButtons + 2)
        {
            pDataArr[idxRowNum * numCol + idxColNum] = -1;
        }
        else
        {
            pDataArr[idxRowNum * numCol + idxColNum] = 0;
        }


        idxRowNum++;
        if (idxColNum < 2)
        {
            // objective cols
            for (  ; idxRowNum < numRow; idxRowNum++)
            {
                pDataArr[idxRowNum * numCol + idxColNum] = 0;
            }
        }
        else
        {
            // data cols
            button = this->_buttonArray[idxColNum-2];
            for (  ; idxRowNum < numRow; idxRowNum++)
            {
                pDataArr[idxRowNum * numCol + idxColNum] = (button & 0x01);
                button >>= 1;
            }
        }
    }

    // set the last column with constraints
    for (int i = 0; i < numRow; i++)
    {
        if (i < 2)
        {
            pDataArr[(i + 1) * numCol - 1] = 0;
        }
        else
        {
            pDataArr[(i + 1) * numCol - 1] = (int)this->_joltageArray[i-2];
        }
    }


    return new IntegerTableau(numRow, numCol, pDataArr, szDataArr);
}