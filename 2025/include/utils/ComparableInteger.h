#ifndef __COMPARABLE_INTEGER_H__
#define __COMPARABLE_INTEGER_H__

#include "IComparable.h"
#include "Integer.h"

class ComparableInteger : public Integer, public IComparable<Integer>
{
    public:
        using Integer::Integer;
        virtual int CompareTo(Integer* other) override;
};

#endif // __COMPARABLE_INTEGER_H__