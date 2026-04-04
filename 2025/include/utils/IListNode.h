#ifndef __I_LIST_LODE_H__
#define __I_LIST_LODE_H__

template <typename T>
class IListNode
{
    public:
        virtual ~IListNode() = default;
        virtual T* GetData() const = 0;
        virtual IListNode<T>* GetNext() const = 0;
        virtual void SetNext(IListNode<T>* pNext) = 0;
};

#endif // __I_LIST_LODE_H__