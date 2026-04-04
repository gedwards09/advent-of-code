#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "IQueue.h"
#include "ListNode.h"

template <typename T>
class Queue : public IQueue<T>
{
    public:
        virtual ~Queue() override;
        Queue();
        virtual void Enqueue(T* data) override;
        virtual T* Dequeue() override;
        virtual void Clear() override;
        virtual int Size() const override;
        virtual bool IsEmpty() const override;

    private:
        int _size;
        IListNode<T>* _head;
        IListNode<T>* _tail;
};

template <typename T>
Queue<T>::~Queue()
{
    this->Clear();
}

template <typename T>
Queue<T>::Queue() : _size(0), _head(NULL), _tail(NULL) {  }

template <typename T>
void Queue<T>::Enqueue(T* data)
{
    IListNode<T>* node;

    node = new ListNode<T>(data);

    if (this->_head == NULL)
    {
        this->_head = node;
        this->_tail = node;
    }
    else
    {
        this->_tail->SetNext(node);
        this->_tail = node;
    }

    this->_size++;
}

template <typename T>
T* Queue<T>::Dequeue()
{
    T* data;
    IListNode<T>* next;

    assert(this->_size > 0);
    assert(this->_head != NULL);
    data = this->_head->GetData();
    next = this->_head->GetNext();
    if (this->_tail == this->_head)
    {
        this->_tail = NULL;
    }
    delete this->_head;
    this->_head = next;

    return data;
}

template <typename T>
void Queue<T>::Clear()
{
    IListNode<T>* current;

    while (this->_head != NULL)
    {
        current = this->_head;
        this->_head = this->_head->GetNext();
        delete current;
    }

    this->_tail = NULL;
    this->_size = 0;
}

template <typename T>
int Queue<T>::Size() const
{
    return this->_size;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return this->_size == 0;
}

#endif // __QUEUE_H__