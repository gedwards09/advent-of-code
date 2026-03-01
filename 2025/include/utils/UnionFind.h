#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <concepts>
#include <iostream>

#include "ComparableInteger.h"
#include "Heap.h"
#include "IHashable.h"
#include "IUnionFind.h"

#define MAX_ITER (1024)
#define ITER_TO_REDUCE (2)

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
        virtual Array<int>* ListComponentSizes(Array<int>* pArray) override;
        virtual int GetComponentCount() const override;

    private:
        Array<T>* _dataArray;
        HashTable<T,int>* _parentIDs;
        int _count;

        int getParentID(T* data) const;
        void setParentID(T* data, int id);
        int findID(T* data);
        void compress(T* data, int id);
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
    
    delete this->_parentIDs;
    this->_parentIDs = NULL;
}

template <typename T>
requires std::derived_from<T, IHashable>
UnionFind<T>::UnionFind() : 
        _dataArray(new Array<T>()), 
        _parentIDs(new HashTable<T,int>()),
        _count(0) {  }

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::Add(T* data)
{
    int newID;

    assert(data != NULL);
    newID = this->_dataArray->Size();
    this->_dataArray->Append(data);
    assert(this->_dataArray->Get(newID) == data);
    assert(this->_parentIDs->Set(data, new int(newID)));
    this->_count++;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::getParentID(T* data) const
{
    int* pid;

    assert(data != NULL);
    assert(this->_parentIDs->Get(data, &pid));
    assert(pid != NULL);

    return *pid;
}

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::setParentID(T* data, int id)
{
    int* pid;

    assert(data != NULL);
    this->_parentIDs->Get(data, &pid);
    assert(pid != NULL);
    *pid = id;
}

template <typename T>
requires std::derived_from<T, IHashable>
T* UnionFind<T>::Find(T* data)
{
    int id;
    T* pHead;

    id = this->findID(data);
    pHead = this->_dataArray->Get(id);
    assert(pHead != NULL);

    return pHead;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::findID(T* data)
{
    T* pChild;
    T* pParent;
    int count;
    int id;

    assert(data != NULL);
    pChild = NULL;
    pParent = data;
    count = 0;
    while (pParent != pChild && count < MAX_ITER)
    {
        count++;
        pChild = pParent;
        id = this->getParentID(pChild);
        pParent = this->_dataArray->Get(id);
    }

    if (count > ITER_TO_REDUCE)
    {
        this->compress(data, id);
    }

    if (count >= MAX_ITER)
    {
        std::cout << "UnionFind:findID:Maximum iterations reached" << std::endl;
    }

    return id;
}

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::compress(T* data, int id)
{
    T* pChild;
    T* pParent;
    int count;
    int parentID;

    assert(data != NULL);
    pChild = NULL;
    pParent = data;
    count = 0;
    while (pParent != pChild && count < MAX_ITER)
    {
        count++;
        pChild = pParent;
        parentID = this->getParentID(pChild);
        if (parentID != id)
        {
            this->setParentID(pChild, id);
        }
        pParent = this->_dataArray->Get(parentID);
    }
}

template <typename T>
requires std::derived_from<T, IHashable>
void UnionFind<T>::Union(T* thisData, T* thatData)
{
    int thisHeadID;
    int thatHeadID;
    T* pHead;

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
        pHead = this->Find(thatData);
        this->setParentID(pHead, thisHeadID);
    }
    else // thisHeadID > thatHeadID
    {
        pHead = this->Find(thisData);
        this->setParentID(pHead, thatHeadID);
    }
}

template <typename T>
requires std::derived_from<T, IHashable>
Array<int>* UnionFind<T>::ListComponentSizes(Array<int>* pArray)
{
    HashTable<T,int> table;
    HashTable<T,int>* pTable;
    Array<T> headDataArray;
    Array<T>* pHeadDataArray;
    T* pData;
    int* pInt;

    pTable = &table;
    pHeadDataArray = &headDataArray;
    for (int i = 0; i < this->_dataArray->Size(); i++)
    {
        pData = this->_dataArray->Get(i);
        pData = this->Find(pData);
        if (pTable->Get(pData, &pInt))
        {
            (*pInt)++;
        }
        else
        {
            assert(pTable->Set(pData, new int(1)));
            pHeadDataArray->Append(pData);
        }
    }

    for (int i = 0; i < pHeadDataArray->Size(); i++)
    {
        pData = pHeadDataArray->Get(i);
        assert(pTable->Get(pData, &pInt));
        pArray->Append(pInt);
    }

    pTable->Clear();
    pHeadDataArray->Clear();

    return pArray;
}

template <typename T>
requires std::derived_from<T, IHashable>
int UnionFind<T>::GetComponentCount() const
{
    return this->_count;
}

#endif // __UNION_FIND_H__