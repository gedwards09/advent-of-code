#include <iostream>

#include "Array.h"
#include "IHashable.h"
#include "Heap.h"

#include "PaperRollMap.h"

int PaperRollMap::CountAccessibleRolls()
{
    int count;
    int xCoord;
    int yCoord;

    count = 0;
    for (xCoord = 0; this->IsValidXCoord(xCoord); xCoord++)
    {
        for (yCoord = 0; this->IsValidYCoord(yCoord); yCoord++)
        {
            if (this->isPaperRoll(xCoord, yCoord) && this->isAccessible(xCoord, yCoord))
            {
                count++;
            }
        }
    }

    return count;
}

bool PaperRollMap::isPaperRoll(int xCoord, int yCoord)
{
    return this->GetCoord(xCoord, yCoord) == PaperRollMap::s_paperRoll;
}

bool PaperRollMap::isAccessible(int xCoord, int yCoord)
{
    return this->countNeighbors(xCoord, yCoord) < ACCESS_LEVEL_CEIL;
}

int PaperRollMap::countNeighbors(int xCoord, int yCoord)
{
    int count;
    int dx;
    int dy;

    count = 0;
    for (dx = -1; dx < 2; dx++)
    {
        for (dy = -1; dy < 2; dy++)
        {
            if (dx == 0 && dy == 0)
            {
                continue;
            }

            if (this->isPaperRoll(xCoord + dx, yCoord + dy))
            {
                count++;
            }
        }
    }

    return count;
}

// int PaperRollMap::ProcessAccessibleRolls(p_hash_table_t pTable, p_heap_t pHeap);
int PaperRollMap::CountAllAccessibleRolls()
{
    hash_table_t table;
    p_hash_table_t pTable;
    p_heap_t pHeap;
    HashableCoordinate* pCoord;
    ComparableInteger* pInt;
    p_heap_entry_t pHeapEntry;
    int count;

    // InitializeDataStructures
    pTable = &table;
    pHeap = new heap_t;
    this->initializeDataStructures(pTable, pHeap);

    count = 0;
    // ProcessAccessibleRolls
    while (true)
    {
        int currentCount = 0;
        while (pHeap->Size() > 0 && pHeap->Peek()->Value()->Value < ACCESS_LEVEL_CEIL)
        {
            currentCount++;
            pHeapEntry = pHeap->Remove();
            pCoord = pHeapEntry->Key();
            PaperRollMap::DecrementNeighbors(pTable, pCoord->X(), pCoord->Y());
            assert(pTable->Delete(pCoord));
            delete pHeapEntry;
        }

        if (currentCount == 0)
        {
            break;
        }

        count += currentCount;

        p_heap_t pSwapHeap = new heap_t;
        while (pHeap->Size() > 0)
        {
            pHeapEntry = pHeap->Remove();
            pCoord = pHeapEntry->Key();
            pTable->Get(pCoord, &pInt);
            if (pInt->Value != pHeapEntry->Value()->Value)
            {
                pHeapEntry->Value()->Value = pInt->Value;
            }
            pSwapHeap->Add(pHeapEntry);
        }
        
        delete pHeap;
        pHeap = pSwapHeap;
        pSwapHeap = NULL;
    }

    delete pHeap;
    return count;
}

void PaperRollMap::DecrementNeighbors(p_hash_table_t pHashTable, int xCoord, int yCoord)
{
    int dx;
    int dy;
    HashableCoordinate* pCoord;
    ComparableInteger* pInt;

    for (dx = -1; dx < 2; dx++)
    {
        for (dy = -1; dy < 2; dy++)
        {
            if (dx == 0 && dy == 0)
            {
                continue;
            }
            
            pCoord = new HashableCoordinate(xCoord + dx, yCoord + dy);
            if (pHashTable->Get(pCoord, &pInt))
            {
                pInt->Value--;
            }
            delete pCoord;
            pCoord = NULL;
        }
    }
}

void PaperRollMap::initializeDataStructures(p_hash_table_t pHashTable, p_heap_t pHeap)
{
    int yCoord;
    int xCoord;
    int neighbors;
    HashableCoordinate* pCoord;
    ComparableInteger* pInt;
    p_heap_entry_t pHeapEntry;

    for (yCoord = 0; this->IsValidYCoord(yCoord); yCoord++)
    {
        for (xCoord = 0; this->IsValidXCoord(xCoord); xCoord++)
        {
            if (this->isPaperRoll(xCoord, yCoord))
            {
                neighbors = this->countNeighbors(xCoord, yCoord);
                pCoord = new HashableCoordinate(xCoord, yCoord);
                pInt = new ComparableInteger(neighbors);
                pHashTable->Set(pCoord, pInt);

                pCoord = new HashableCoordinate(xCoord, yCoord);
                pInt = new ComparableInteger(neighbors);
                pHeapEntry = new heap_entry_t(pCoord, pInt);
                pHeap->Add(pHeapEntry);
            }
        }
    }
}