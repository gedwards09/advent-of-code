#include <iostream>

#include "DigitBound.h"
#include "SortableArray.h"

#include "IngredientInventory.h"

IngredientInventory::IngredientInventory(
        std::string contents[], size_t szContents) :
        _ranges(NULL), _ids(NULL)
{
    int phase = 0;
    std::string line;

    this->_ranges = new Array<Range>();
    this->_ids = new Array<DigitString>();

    for (size_t i = 0; i < szContents; i++)
    {
        line = contents[i];
        if (line.size() == 0)
        {
            phase++;
        }
        else if (phase == 0)
        {
            this->_ranges->Append(new Range(line));
        }
        else
        {
            this->_ids->Append(new DigitString(line));
        }
    }
}

int IngredientInventory::CountIngredients()
{
    int count;
    DigitString* pid;
    Range* pRange;

    count = 0;
    for (int i = 0; i < this->_ids->Size(); i++)
    {
        pid = this->_ids->Get(i);
        for (int j = 0; j < this->_ranges->Size(); j++)
        {
            pRange = this->_ranges->Get(j);
            if (pRange->InRange(pid))
            {
                count++;
                break;
            }
        }
    }

    return count;
}

long long IngredientInventory::CountEntireRange()
{
    SortableArray<DigitBound> arr;
    SortableArray<DigitBound>* parr;
    Range* pRange;
    DigitBound* pDigitBound;
    long long count;
    DigitBound* pPrevDigitBound;
    int nestLevel;


    parr = &arr;
    for (int i = 0; i < this->_ranges->Size(); i++)
    {
        pRange = this->_ranges->Get(i);
        pDigitBound = new DigitBound(pRange->GetLower(), DigitBoundEnum::Lower);
        parr->Append(pDigitBound);
    }
    for (int i = 0; i < this->_ranges->Size(); i++)
    {
        pRange = this->_ranges->Get(i);
        pDigitBound = new DigitBound(pRange->GetUpper(), DigitBoundEnum::Upper);
        parr->Append(pDigitBound);
    }

    parr->Sort();

    count = 0;
    pPrevDigitBound = NULL;
    nestLevel = 0;
    for (int i = 0; i < parr->Size(); i++)
    {
        pDigitBound = parr->Get(i);
        if (pPrevDigitBound != NULL && nestLevel > 0)
        {
            count += pDigitBound->DifferenceWith(pPrevDigitBound);
        }

        if (pDigitBound->IsLower())
        {
            nestLevel++;
        }
        else
        {
            nestLevel--;
            if (nestLevel == 0)
            {
                count++;
            }
        }

        pPrevDigitBound = pDigitBound;
    }

    parr->DeleteAllAndClear();
    return count;
}