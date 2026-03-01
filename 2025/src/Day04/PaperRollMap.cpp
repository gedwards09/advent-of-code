#include <cassert>

#include "Coordinate.h"

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

int PaperRollMap::CountAllAccessibleRolls()
{
    hash_table_t table;
    p_hash_table_t pTable;
    p_list_t pAccessibleList;
    p_list_t pInaccessibleList;
    int count;

    pTable = &table;
    pAccessibleList = new list_t();
    pInaccessibleList = new list_t();
    this->initializeDataStructures(pTable, pAccessibleList, pInaccessibleList);

    count = 0;
    while (true)
    {
        if (pAccessibleList->IsEmpty())
        {
            break;
        }

        count += pAccessibleList->Size();
        PaperRollMap::ProcessAccessibleList(pTable, pAccessibleList);
        pInaccessibleList = PaperRollMap::ProcessInaccessibleList(pTable, pAccessibleList, pInaccessibleList);
    }

    pInaccessibleList->DeleteAllAndClear();
    delete pInaccessibleList;
    delete pAccessibleList;
    return count;
}

void PaperRollMap::initializeDataStructures(p_hash_table_t pHashTable, 
        p_list_t pAccessibleList, p_list_t pInaccessibleList)
{
    int yCoord;
    int xCoord;
    int neighbors;
    p_entry_t pCoord;
    int* pInt;

    for (yCoord = 0; this->IsValidYCoord(yCoord); yCoord++)
    {
        for (xCoord = 0; this->IsValidXCoord(xCoord); xCoord++)
        {
            if (this->isPaperRoll(xCoord, yCoord))
            {
                neighbors = this->countNeighbors(xCoord, yCoord);
                pCoord = new HashableCoordinate(new Coordinate(xCoord, yCoord));
                pInt = new int(neighbors);
                pHashTable->Set(pCoord, pInt);

                pCoord = new HashableCoordinate(new Coordinate(xCoord, yCoord));
                if (neighbors < ACCESS_LEVEL_CEIL)
                {
                    pAccessibleList->Append(pCoord);
                }
                else
                {
                    pInaccessibleList->Append(pCoord);
                }
            }
        }
    }
}

void PaperRollMap::ProcessAccessibleList(p_hash_table_t pHashTable, p_list_t pAccessibleList)
{
    p_entry_t pCoord;

    for (int i = 0; i < pAccessibleList->Size(); i++)
    {
        pCoord = pAccessibleList->Get(i);
        PaperRollMap::DecrementNeighbors(pHashTable, pCoord->X(), pCoord->Y());
        assert(pHashTable->Delete(pCoord));
    }
    pAccessibleList->DeleteAllAndClear();
}

void PaperRollMap::DecrementNeighbors(HashTable<HashableCoordinate, int>* pHashTable, int xCoord, int yCoord)
{
    int dx;
    int dy;
    HashableCoordinate* pCoord;
    int* pInt;

    for (dx = -1; dx < 2; dx++)
    {
        for (dy = -1; dy < 2; dy++)
        {
            if (dx == 0 && dy == 0)
            {
                continue;
            }
            
            pCoord = new HashableCoordinate(new Coordinate(xCoord + dx, yCoord + dy));
            if (pHashTable->Get(pCoord, &pInt))
            {
                (*pInt)--;
            }
            delete pCoord;
            pCoord = NULL;
        }
    }
}

p_list_t PaperRollMap::ProcessInaccessibleList(p_hash_table_t pHashTable, p_list_t pAccessibleList, p_list_t pInaccessibleList)
{
    p_list_t pInaccessibleSwapList;
    p_entry_t pCoord;
    int* pInt;

    pInaccessibleSwapList = new list_t();
    for (int i = 0; i < pInaccessibleList->Size(); i++)
    {
        pCoord = pInaccessibleList->Get(i);
        assert(pHashTable->Get(pCoord, &pInt));
        if (*pInt < ACCESS_LEVEL_CEIL)
        {
            pAccessibleList->Append(pCoord);
        }
        else
        {
            pInaccessibleSwapList->Append(pCoord);
        }
    }

    delete pInaccessibleList;
    pInaccessibleList = NULL;
    return pInaccessibleSwapList;
}