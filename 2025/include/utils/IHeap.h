#ifndef __I_HEAP_H__
#define __I_HEAP_H__

#include <concepts>

#include "IComparable.h"

template<typename T, typename S = T>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
class IHeap
{
    public:
        virtual ~IHeap() = default;
        virtual Add(T* item) = 0;
        virtual T* Remove() = 0;
        virtual T* Peek() = 0;
        virtual bool IsEmpty() = 0;
        virtual int Size() = 0;
        virtual void Clear() = 0;
};

#endif // __I_HEAP_H__