#ifndef __HEAP_H__
#define __HEAP_H__

#include <cassert>
#include <concepts>

#include "IComparable.h"
#include "IHeap.h"

#define HEAP_DEFAULT_SIZE (16)
#define FIRST_INDEX (1)

template<typename T, typename S = T>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
class Heap : IHeap<T, S>
{
    public:
        virtual ~Heap() override;
        Heap();
        virtual Add(T* item) override;
        virtual T* Remove() override;
        virtual T* Peek() override;
        virtual bool IsEmpty() override;
        virtual int Size() override;
        virtual void Clear() override;

    private:
        T** _array;
        int _capacity;
        int _count;

        void grow();
        void upHeap(int index);
        static void Swap(T** array, int szArray, int leftIdx, int rightIdx);
        void downHeap(int index);
        static int GrowCapacity(int capacity);
};

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
Heap<T,S>::~Heap()
{
    for (int i = 1; i <= this->_count; i++)
    {
        delete this->_array[i];
        this->_array[i] = NULL;
    }
    free(this->_array);
    this->_array = NULL;
    this->_count = 0;
    this->_capacity = 0;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
Heap<T,S>::Heap() : _array(NULL), _capacity(0), _count(0) {  }

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
int Heap<T,S>::Add(T* item)
{
    assert(item != NULL);

    if (this->_count + 1 >= this->_capacity)
    {
        this->grow();
    }

    this->_count++;
    this->_array[this->_count] = item;
    this->upHeap(this->_count);

    return this->_count;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void Heap<T,S>::grow()
{
    int capacity;
    T** array;

    capacity = Heap<T,S>::GrowCapacity(this->_capacity);
    array = (T**)realloc(this->_array, sizeof(T*) * capacity);
    assert(array != NULL);
    if (this->_capacity < HEAP_DEFAULT_SIZE)
    {
        // the first time we allocate make sure 0-index slot is nulled
        array[0] = NULL;
    }

    this->_array = array;
    this->_capacity = capacity;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
int Heap<T,S>::GrowCapacity(int capacity)
{
    if (capacity < HEAP_DEFAULT_SIZE)
    {
        capacity = HEAP_DEFAULT_SIZE;
    }
    else
    {
        capacity *= 2;
    }

    return capacity;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void Heap<T,S>::upHeap(int index)
{
    int parentIndex;

    assert(0 <= index && index < this->_capacity);
    if (index == 1)
    {
        return;
    }
    parentIndex = index/2;
    while (parentIndex > 0 && this->_array[parentIndex]->CompareTo(this->_array[index]) > 0)
    {
        Heap<T,S>::Swap(this->_array, this->_count, parentIndex, index);
        index = parentIndex;
        parentIndex /= 2;
    }
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void Heap<T,S>::Swap(T** array, int size, int leftIdx, int rightIdx)
{
    T* tmp;

    assert(0 < leftIdx && leftIdx <= size && 0 < rightIdx && rightIdx <= size);
    if (leftIdx == rightIdx)
    {
        return;
    }
    tmp = array[leftIdx];
    array[leftIdx] = array[rightIdx];
    array[rightIdx] = tmp;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
T* Heap<T,S>::Remove()
{
    T* out;
    int last;

    assert(this->_count > 0);
    last = this->_count;
    out = this->_array[FIRST_INDEX];
    this->_array[FIRST_INDEX] = NULL;
    Heap<T,S>::Swap(this->_array, this->_count, FIRST_INDEX, last);
    this->_count--;
    if (this->_count > 0)
    {
        this->downHeap(FIRST_INDEX);
    }

    return out;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void Heap<T,S>::downHeap(int index)
{
    int stopIdx;
    int childIndex;

    assert(0 < index && index <= this->_count);
    stopIdx = this->_count / 2;
    while (index <= stopIdx)
    {
        childIndex = 2 * index;
        if (childIndex + 1 <= this->_count && this->_array[childIndex]->CompareTo(this->_array[childIndex+1]) > 0)
        {
            childIndex++;
        }

        if (this->_array[index]->CompareTo(this->_array[childIndex]) > 0)
        {
            Heap<T,S>::Swap(this->_array, this->_count, index, childIndex);
            index = childIndex;
        }
        else
        {
            return;
        }
    }
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
T* Heap<T,S>::Peek()
{
    if (this->_count == 0)
    {
        return NULL;
    }

    return this->_array[FIRST_INDEX];
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
bool Heap<T,S>::IsEmpty()
{
    return this->_count == 0;
}

template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
int Heap<T,S>::Size()
{
    return this->_count;
}


template<typename T, typename S>
requires std::derived_from<T, S> && std::derived_from<T, IComparable<S>>
void Heap<T,S>::Clear()
{
    for (int i = 1; i <= this->_count; i++)
    {
        delete this->_array[i];
        this->_array[i] = NULL;
    }
    free(this->_array);
    this->_array = NULL;
    this->_count = 0;
    this->_capacity = 0;
}





#endif // __HEAP_H__