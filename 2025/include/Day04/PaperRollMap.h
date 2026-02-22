#ifndef __PAPER_ROLL_MAP__
#define __PAPER_ROLL_MAP__

#include "ComparableEntry.h"
#include "ComparableInteger.h"
#include "HashableCoordinate.h"
#include "HashTable.h"
#include "Heap.h"
#include "Map.h"

#define ACCESS_LEVEL_CEIL (4)

typedef Entry<HashableCoordinate, ComparableInteger> entry_t;

typedef HashTable<HashableCoordinate,ComparableInteger> hash_table_t;
typedef hash_table_t* p_hash_table_t;

typedef ComparableEntry<HashableCoordinate,ComparableInteger,Integer> heap_entry_t;
typedef heap_entry_t* p_heap_entry_t;

typedef Heap<ComparableEntry<HashableCoordinate, ComparableInteger, Integer>, Entry<HashableCoordinate, ComparableInteger>> heap_t;
typedef heap_t* p_heap_t;

class PaperRollMap : public Map
{
    public:
        using Map::Map;
        int CountAccessibleRolls();
        int CountAllAccessibleRolls();

    private:
        static const char s_paperRoll = '@';

        bool isPaperRoll(int xCoord, int yCoord);
        bool isAccessible(int xCoord, int yCoord);
        int countNeighbors(int xCoord, int yCoord);
        void initializeDataStructures(p_hash_table_t pHashTable, p_heap_t pHeap);
        static void DecrementNeighbors(p_hash_table_t pHashTable, int xCoord, int yCoord);
};

#endif // __PAPER_ROLL_MAP__