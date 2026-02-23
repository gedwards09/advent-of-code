#ifndef __DIGIT_STRING_H__
#define __DIGIT_STRING_H__

#include <string>

#include "IComparable.h"

#define BASE10 (10)

class DigitString : public IComparable<DigitString>
{
    public:
        DigitString(std::string line);
        int CompareTo(DigitString* other);
        int Length();
        int DigitInPlace(int i);
        void Print();
        static bool IsDigitString(std::string line);
        long long DifferenceWith(DigitString* other);

    private:
        std::string _string;
        int _szString;

        static const char s_charZero = '0';
        static const char s_charNine = '9';
};

#endif // __DIGIT_STRING_H__