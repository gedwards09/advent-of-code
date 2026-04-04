#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__

#include "IListNode.h"

template <typename T>
class ListNode : public IListNode<T>
{
    public:
        ~ListNode();
        ListNode(T* data);
        virtual T* GetData() const override;
        virtual IListNode<T>* GetNext() const override;
        virtual void SetNext(IListNode<T>* next) override;

    private:
        T* _data;
        IListNode<T>* _next;
};

template <typename T>
ListNode<T>::~ListNode()
{
    this->_data = NULL;
    this->_next = NULL;
}

template <typename T>
ListNode<T>::ListNode(T* data) : _data(data), _next(NULL) {  }

template <typename T>
T* ListNode<T>::GetData() const
{
    return this->_data;
}

template <typename T>
IListNode<T>* ListNode<T>::GetNext() const
{
    return this->_next;
}

template <typename T>
void ListNode<T>::SetNext(IListNode<T>* next)
{
    this->_next = next;
}

#endif // __LIST_NODE_H__