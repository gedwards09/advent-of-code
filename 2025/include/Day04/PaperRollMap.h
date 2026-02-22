#ifndef __PAPER_ROLL_MAP__
#define __PAPER_ROLL_MAP__

#include "Array.h"
#include "HashableCoordinate.h"
#include "HashTable.h"
#include "Map.h"

#define ACCESS_LEVEL_CEIL (4)

typedef HashableCoordinate entry_t;
typedef entry_t* p_entry_t;

typedef HashTable<HashableCoordinate,int> hash_table_t;
typedef hash_table_t* p_hash_table_t;

typedef Array<HashableCoordinate> list_t;
typedef list_t* p_list_t;

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
        void initializeDataStructures(p_hash_table_t pHashTable,
                p_list_t pAccessibleList, p_list_t pInaccessibleList);
        static void ProcessAccessibleList(p_hash_table_t pHashTable, p_list_t pAccessibleList);
        static void DecrementNeighbors(p_hash_table_t pHashTable, int xCoord, int yCoord);
        static p_list_t ProcessInaccessibleList(p_hash_table_t pHashTable,
                p_list_t pAccessibleList, p_list_t pInaccessibleList);
};

#endif // __PAPER_ROLL_MAP__