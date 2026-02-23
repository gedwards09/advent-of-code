#include <cstdint>

#include "DigitBoundEnum.h"
#include "DigitString.h"

class DigitBound : public IComparable<DigitBound>
{
    public:
        DigitBound(DigitString* digit, DigitBoundEnum type);
        bool IsLower();
        bool IsUpper();
        virtual int CompareTo(DigitBound* other) override;
        long long DifferenceWith(DigitBound* prev);
        void Print();

    private:
        DigitString* _digit;
        const DigitBoundEnum _type;
};