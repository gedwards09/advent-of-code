#ifndef __I_UNION_FIND_H__
#define __I_UNION_FIND_H__

#include "Array.h"
#include "HashTable.h"
#include "IUnionFindEntry.h"

template <typename T>
class IUnionFind
{
    public:
        virtual ~IUnionFind() = default;
        virtual void Add(T* data) = 0;
        virtual T* Find(T* data) = 0;
        virtual void Union(T* data, T* other) = 0;
        virtual Array<int>* ListComponentSizes(Array<int>* pArray) = 0;
        virtual int GetComponentCount() const = 0;
};

#endif // __I_UNION_FIND_H__