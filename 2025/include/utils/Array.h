#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <cstddef>
#include <stdexcept>

#define DEFAULT_CAPACITY (64)

template <typename T>
class Array
{
    public:
        ~Array();
        Array();
        void Append(T* value);
        T* Get(int i);
        bool IsEmpty();
        int Size();

    private:
        int _sz;
        int _capacity;
        T** _array;

        void grow();
        static int GrowCapacity(int capacity);
};

template <typename T>
Array<T>::Array() : _sz(0), _capacity(0), _array(NULL) {  }

template <typename T>
Array<T>::~Array()
{
    for (int i = 0; i < this->_sz; i++)
    {
        free(this->_array[i]);
        this->_array[i] = NULL;
    }

    if (this->_array != NULL)
    {
        free(this->_array);
        this->_array = NULL;
    }
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
    int newCapacity;
    T** result;

    newCapacity = Array<T>::GrowCapacity(this->_capacity);
    result = (T**)realloc(this->_array, sizeof(T*) * newCapacity);
    if (result == NULL)
    {
        throw std::runtime_error("Array.cpp:Out of memory error.");
    }
    this->_array = result;
    this->_capacity = newCapacity;
}

template <typename T>
int Array<T>::GrowCapacity(int capacity)
{
    if (capacity < DEFAULT_CAPACITY)
    {
        capacity = DEFAULT_CAPACITY;
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
    if (i < 0 || i >= _sz)
    {
        throw new std::runtime_error("Array: Out of bounds index error");
    }

    return _array[i];
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
#endif // __ARRAY_H__