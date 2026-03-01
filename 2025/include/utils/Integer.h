#ifndef __INTEGER_H__
#define __INTEGER_H__

#include "IComparable.h"

class Integer : public IComparable<Integer>
{
    public:
        Integer();
        Integer(int value);
        Integer(int* pValue);
        int Value;
        virtual int CompareTo(Integer* other) const override;

    private:
        static int Deref(int* pValue);
};

#endif // __INTEGER_H__