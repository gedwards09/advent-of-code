#ifndef __RANGE_H__
#define __RANGE_H__

#include <string>

#include "DigitString.h"

class Range
{
    public:
        Range(std::string line);
        DigitString* GetLower();
        DigitString* GetUpper();
        bool InRange(DigitString* d);
        void Print();

    private:
        DigitString* _lower;
        DigitString* _upper;

        static const char s_delim = '-';
};

#endif // __RANGE_H__