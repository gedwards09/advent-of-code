#ifndef __I_PAIR_H__
#define __I_PAIR_H__

template <typename T>
class IPair
{
    public:
        virtual ~IPair() = default;
        virtual T* GetLeft() const = 0;
        virtual T* GetRight() const = 0;
};

#endif // __I_PAIR_H__