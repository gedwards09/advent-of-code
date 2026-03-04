
#include "Array.h"
#include "Coordinate.h"
#include "StringSplitter.h"

#include "JunctionConnector.h"

#define COMPONENT_NUM (3)


JunctionConnector::~JunctionConnector()
{
    delete this->_heap;
    this->_heap = NULL;
    delete this->_unionFind;
    this->_unionFind = NULL;
}

JunctionConnector::JunctionConnector(std::string contents[], size_t szContents) : 
        _heap(new heap_t()),
        _unionFind(new union_find_t()),
        _iterLimit(szContents > ITER_LIMIT_BOUNDARY ? BIG_ITER_LIMIT : SMALL_ITER_LIMIT)
{
    array_t array;

    this->parseCoordinates(contents, szContents, &array);
    this->buildEdges(&array);
    array.Clear();
}

void JunctionConnector::parseCoordinates(std::string contents[], size_t szContents, array_t* pArray)
{
    std::string line;
    std::vector<std::string> vec;
    int pack[SZ_DIM];
    coord_t* pCoord;

    for (size_t i = 0; i < szContents; i++)
    {
        line = contents[i];
        vec = StringSplitter::Split(line, JunctionConnector::s_comma);
        assert(vec.size() == SZ_DIM);
        for (int j = 0; j < SZ_DIM; j++)
        {
            pack[j] = std::atoi(vec[j].c_str());
        }
        pCoord = JunctionConnector::ConstructCoordinate(pack, SZ_DIM);
        pArray->Append(pCoord);
        this->_unionFind->Add(pCoord);
    }
}

coord_t* JunctionConnector::ConstructCoordinate(int coordArr[], int sz)
{
    assert(sz >= SZ_DIM);
    
    return new HashableCoordinate(coordArr[0], coordArr[1], coordArr[2]);
}

void JunctionConnector::buildEdges(array_t* pArray)
{
    coord_t* pCoord;
    coord_t* pOther;
    pair_t* pPair;

    for (int i = 0; i < pArray->Size(); i++)
    {
        pCoord = pArray->Get(i);
        for (int j = i + 1; j < pArray->Size(); j++)
        {
            pOther = pArray->Get(j);
            pPair = new pair_t(pCoord, pOther);
            this->_heap->Add(pPair);
        }
    }
}

long long JunctionConnector::SolveLargestCircuits()
{
    pair_t* pPair;

    for (int i = 0; i < this->_iterLimit; i++)
    {
        pPair = this->_heap->Remove();
        this->_unionFind->Union(pPair->GetLeft(), pPair->GetRight());
        delete pPair;
    }

    delete this->_heap;
    this->_heap = NULL;
    return this->multiplyTopConnectedSizes(COMPONENT_NUM);
}


long long JunctionConnector::multiplyTopConnectedSizes(int num)
{
    Heap<Integer> heap(false);
    Heap<Integer>* pHeap;
    long long out;
    Integer* poInt;

    pHeap = this->_unionFind->ComponentSizeHeap(&heap);
    out = 1;
    for (int i = 0; i < num; i++)
    {
        poInt = pHeap->Remove();
        out *= poInt->Value;
        delete poInt;
    }

    return out;
}

long long JunctionConnector::SolveConnectedCircuit()
{
    pair_t* pPair;
    long long out;

    out = 0;
    while (this->_unionFind->GetComponentCount() > 1)
    {
        pPair = this->_heap->Remove();
        this->_unionFind->Union(pPair->GetLeft(), pPair->GetRight());
        if (this->_unionFind->GetComponentCount() == 1)
        {
            out = pPair->GetLeft()->X() * (long long)pPair->GetRight()->X();
        }
        delete pPair;
    }

    delete this->_heap;
    this->_heap = NULL;
    return out;
}