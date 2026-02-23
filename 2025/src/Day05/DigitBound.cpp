#include <iostream>
#include <cassert>

#include "DigitBound.h"

DigitBound::DigitBound(DigitString* digit, DigitBoundEnum type) : _digit(digit), _type(type) {  }

bool DigitBound::IsLower()
{
    return this->_type == DigitBoundEnum::Lower;
}

bool DigitBound::IsUpper()
{
    return this->_type == DigitBoundEnum::Upper;
}

int DigitBound::CompareTo(DigitBound* other)
{
    int rc;

    rc = this->_digit->CompareTo(other->_digit);
    if (rc != 0)
    {
        return rc;
    }
    else
    {
        return (int)this->_type - (int)other->_type;
    }
}

long long DigitBound::DifferenceWith(DigitBound* prev)
{
    return this->_digit->DifferenceWith(prev->_digit);
}

void DigitBound::Print()
{
    this->_digit->Print();
    std::cout << " " << (this->_type == DigitBoundEnum::Lower ? '<' : '>');
}