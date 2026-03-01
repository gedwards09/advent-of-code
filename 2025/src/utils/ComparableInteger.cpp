#include "ComparableInteger.h"

int ComparableInteger::CompareTo(Integer* other)
{
    return this->Value - other->Value;
}