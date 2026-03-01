#ifndef __PAIR_H__
#define __PAIR_H__

#include "IPair.h"

template <typename T>
class Pair : IPair<T>
{
    public:
        Pair(T* left, T* right);
        virtual T* GetLeft() const override;
        virtual T* GetRight() const override;

    private:
        T* _left;
        T* _right;
};

template <typename T>
Pair<T>::Pair(T* left, T* right) : _left(left), _right(right) {  }

template <typename T>
T* Pair<T>::GetLeft() const
{
    return this->_left;
}

template <typename T>
T* Pair<T>::GetRight() const
{
    return this->_right;
}

#endif // __PAIR_H__
