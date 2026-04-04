#ifndef __I_QUEUE_H__
#define __I_QUEUE_H__

template <typename T>
class IQueue
{
    public:
        virtual ~IQueue() = default;
        virtual void Enqueue(T* data) = 0;
        virtual T* Dequeue() = 0;
        virtual void Clear() = 0;
        virtual int Size() const = 0;
        virtual bool IsEmpty() const = 0;
};

#endif // __I_QUEUE_H__