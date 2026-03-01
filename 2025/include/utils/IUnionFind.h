#ifndef __I_UNION_FIND_H__
#define __I_UNION_FIND_H__

#include "Heap.h"
#include "Integer.h"

template <typename T>
class IUnionFind
{
    public:
        virtual ~IUnionFind() = default;
        virtual void Add(T* data) = 0;
        virtual T* Find(T* data) = 0;
        virtual void Union(T* data, T* other) = 0;
        virtual Heap<Integer>* ComponentSizeHeap(Heap<Integer>* pHeap) = 0;
        virtual int GetComponentCount() const = 0;
};

#endif // __I_UNION_FIND_H__