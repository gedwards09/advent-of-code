#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <concepts>

#include "Array.h"
#include "HashTable.h"
#include "Heap.h"
#include "IHashable.h"
#include "Integer.h"
#include "IUnionFind.h"

template <typename T>
requires std::derived_from<T, IHashable>
class UnionFind : public IUnionFind<T>
{
    public:
        virtual ~UnionFind() override;
        UnionFind();
        virtual void Add(T* data) override;
        virtual T* Find(T* data) override;
        virtual void Union(T* thisData, T* thatData) override;
        virtual Heap<Integer>* ComponentSizeHeap(Heap<Integer>* pHeap) override;
        virtual int GetComponentCount() const override;

    private:
        Array<T>* _dataArray;
        Array<int>* _parentIDArray;
        HashTable<T,int>* _idTable;
        int _count;

        int getID(T* data) const;
        int getParentID(int data) const;
        void setParentID(int id, int parentID);
        int findID(T* data);
};

template <typename T>
requires std::derived_from<T, IHashable>
UnionFind<T>::~UnionFind()
{
    if (this->_dataArray != NULL)
    {
        this->_dataArray->Clear();
        delete this->_dataArray;
        this->_dataArray = NULL;
    }

    if (this->_parentIDArray != NULL)
    {
        this->_parentIDArray->Clear();
        delete this->_parentIDArray;
        this->_parentIDArray = NULL;
    }
    
    if (this->_idTable != NULL)
    {
        delete this->_idTable;
        this->_idTable = NULL;
    }
}

template <typename T>
requires std::derived_from<T, IHashable>
UnionFind<T>::UnionFind() : 
        _dataArray(NULL), 
        _parentIDArray(NULL),
        _idTable(NULL),
        _count(0) {  }

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::Add(T* data)
{
    int newID;
    int* pID;

    assert(data != NULL);
    if (this->_count == 0)
    {
        _dataArray = new Array<T>();
        this->_parentIDArray = new Array<int>();
        this->_idTable = new HashTable<T,int>();
    }

    newID = this->_count;
    pID = new int(newID);
    this->_dataArray->Append(data);
    this->_parentIDArray->Append(pID);
    assert(this->_dataArray->Get(newID) == data);
    assert(this->_parentIDArray->Get(newID) == pID);
    assert(this->_idTable->Set(data, pID));
    this->_count++;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::getID(T* data) const
{
    int* pID;

    assert(data != NULL);
    assert(this->_idTable->Get(data, &pID));
    assert(pID != NULL);

    return *pID;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::getParentID(int ID) const
{
    int* pID;

    pID = this->_parentIDArray->Get(ID);
    assert(pID != NULL);

    return *pID;
}

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::setParentID(int id, int parentID)
{
    *(this->_parentIDArray->Get(id)) = parentID;
}

template <typename T>
requires std::derived_from<T, IHashable>
T* UnionFind<T>::Find(T* data)
{
    int id;

    id = this->findID(data);

    return this->_dataArray->Get(id);
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::findID(T* data)
{
    int childID;
    int parentID;
    int parentParentID;

    childID = -1; // never an ID
    parentID = this->getID(data);
    while (parentID != childID)
    {
        childID = parentID;
        parentID = this->getParentID(childID);
        parentParentID = this->getParentID(parentID);
        this->setParentID(childID, parentParentID);
    }

    return parentID;
}

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::Union(T* thisData, T* thatData)
{
    int thisHeadID;
    int thatHeadID;

    thisHeadID = this->findID(thisData);
    thatHeadID = this->findID(thatData);
    if (thisHeadID == thatHeadID)
    {
        return;
    }
    
    // else merge
    this->_count--;
    if (thisHeadID < thatHeadID)
    {
        this->setParentID(thatHeadID, thisHeadID);
    }
    else // thisHeadID > thatHeadID
    {
        this->setParentID(thisHeadID, thatHeadID);
    }
}

template <typename T>
requires std::derived_from<T, IHashable>
Heap<Integer>* UnionFind<T>::ComponentSizeHeap(Heap<Integer>* pHeap)
{
    int* pArr;
    T* pData;
    int headID;

    pArr = (int*)calloc(this->_dataArray->Size(), sizeof(int));
    assert(pArr != NULL);
    for (int i = 0; i < this->_dataArray->Size(); i++)
    {
        pData = this->_dataArray->Get(i);
        headID = this->findID(pData);
        pArr[headID]++;
    }

    for (int i = 0; i < this->_dataArray->Size(); i++)
    {
        if (pArr[i] > 0)
        {
            pHeap->Add(new Integer(pArr[i]));
        }
    }

    free(pArr);
    pArr = NULL;
    return pHeap;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::GetComponentCount() const
{
    return this->_count;
}

#endif // __UNION_FIND_H__