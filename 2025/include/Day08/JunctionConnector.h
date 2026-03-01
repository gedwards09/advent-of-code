#include <string>

#include "HashableCoordinatePair.h"
#include "HashableCoordinate.h"
#include "Heap.h"
#include "UnionFind.h"

#define SZ_DIM (3)
#define SMALL_ITER_LIMIT (10)
#define BIG_ITER_LIMIT (1000)
#define ITER_LIMIT_BOUNDARY (128)

typedef HashableCoordinate coord_t;
typedef UnionFind<IHashableCoordinate> union_find_t;
typedef HashableCoordinatePair pair_t;
typedef Heap<pair_t> heap_t;
typedef HashTable<IHashableCoordinate,int> table_t;

class JunctionConnector
{
    public:
        ~JunctionConnector();
        JunctionConnector(std::string contents[], size_t szContents);
        long long SolveLargestCircuits();
        long long SolveConnectedCircuit();

    private:
        static const char s_comma = ',';

        heap_t* _heap;
        union_find_t* _unionFind;
        const int _iterLimit;

        static coord_t* ConstructCoordinate(int coordArr[], int sz);
        long long multiplyTopConnectedSizes(int num);
};