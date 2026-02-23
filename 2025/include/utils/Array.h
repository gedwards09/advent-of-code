#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <cassert>

#define ARRAY_DEFAULT_CAPACITY (64)

template <typename T>
class Array
{
    public:
        ~Array();
        Array();
        void Append(T* value);
        T* Get(int i);
        bool IsValidIndex(int i);
        bool IsEmpty();
        int Size();
        void Clear();
        void DeleteAllAndClear();
        void Swap(int i, int j);

    private:
        T** _array;
        int _capacity;
        int _sz;

        void grow();
        static int GrowCapacity(int capacity);
};

template <typename T>
Array<T>::Array() : _array(NULL), _capacity(0), _sz(0) {  }

template <typename T>
Array<T>::~Array()
{
    this->Clear();
}

template <typename T>
void Array<T>::Append(T* value)
{
    if (this->_capacity < this->_sz + 1)
    {
        this->grow();
    }

    this->_array[this->_sz] = value;
    this->_sz++;
}

template <typename T>
void Array<T>::grow()
{
    int capacity;
    T** array;

    capacity = Array<T>::GrowCapacity(this->_capacity);
    array = (T**)realloc(this->_array, sizeof(T*) * capacity);
    assert(array != NULL);
    for (int i = this->_capacity; i < capacity; i++)
    {
        array[i] = NULL;
    }
    this->_array = array;
    this->_capacity = capacity;
}

template <typename T>
int Array<T>::GrowCapacity(int capacity)
{
    if (capacity < ARRAY_DEFAULT_CAPACITY)
    {
        capacity = ARRAY_DEFAULT_CAPACITY;
    }
    else
    {
        capacity *= 2;
    }

    return capacity;
}

template <typename T>
T* Array<T>::Get(int i)
{
    assert(Array<T>::IsValidIndex(i));
    return _array[i];
}

template <typename T>
bool Array<T>::IsValidIndex(int i)
{
    return 0 <= i && i < this->_sz;
}

template <typename T>
bool Array<T>::IsEmpty()
{
    return this->_sz == 0;
}

template <typename T>
int Array<T>::Size()
{
    return this->_sz;
}

template <typename T>
void Array<T>::Clear()
{
    free(this->_array);
    this->_array = NULL;
    this->_capacity = 0;
    this->_sz = 0;
}

template <typename T>
void Array<T>::DeleteAllAndClear()
{
    for (int i = 0; i < this->_sz; i++)
    {
        delete this->_array[i];
        this->_array[i] = NULL;
    }
    this->Clear();
}

template <typename T>
void Array<T>::Swap(int i, int j)
{
    T* swap;

    assert(this->IsValidIndex(i) && this->IsValidIndex(j));
    if (i == j)
    {
        return;
    }

    swap = this->_array[i];
    this->_array[i] = this->_array[j];
    this->_array[j] = swap;
}


#endif // __ARRAY_H__