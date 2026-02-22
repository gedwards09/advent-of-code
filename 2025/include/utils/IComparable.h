#ifndef __I_COMPARABLE_H__
#define __I_COMPARABLE_H__

template <typename T>
class IComparable
{
    public:
        virtual ~IComparable() = default;
        virtual int CompareTo(T* other) = 0;
};

#endif // __I_COMPARABLE_H__