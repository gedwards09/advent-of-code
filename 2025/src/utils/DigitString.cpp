#include <cassert>
#include <iostream>

#include "DigitString.h"

DigitString::DigitString(std::string line) : _string(), _szString(0)
{
    assert(DigitString::IsDigitString(line));
    this->_string = line;
    this->_szString = line.length();
}

// static
bool DigitString::IsDigitString(std::string digitStr)
{
    // "" is not a number
    if (digitStr.length() == 0)
    {
        return false;
    }

    for (size_t i = 0; i < digitStr.length(); i++)
    {
        if (DigitString::s_charZero <= digitStr[i] && digitStr[i] <= DigitString::s_charNine)
        {
            continue;
        }

        return false;
    }

    return true;
}

int DigitString::Length()
{
    return this->_szString;
}

int DigitString::DigitInPlace(int i)
{
    assert(0 <= i && i < this->_szString);
    return DigitString::DigitValue(this->_string[i]);
}

int DigitString::DigitValue(char c)
{
    return (int)(c - DigitString::s_charZero);
}

int DigitString::CompareTo(DigitString* other)
{
    int otherLen;
    int thisDigit;
    int otherDigit;

    otherLen = other->Length();

    if (this->_szString != otherLen)
    {
        return this->_szString - otherLen;
    }

    for (int i = 0; i < this->_szString; i++)
    {
        thisDigit = this->DigitInPlace(i);
        otherDigit = other->DigitInPlace(i);
        if (thisDigit != otherDigit)
        {
            return thisDigit - otherDigit;
        }
    }

    return 0; //equal
}

long long DigitString::DifferenceWith(DigitString* other)
{
    int szDiff;
    long long difference;

    // require (this) >= (other)
    if (this->CompareTo(other) < 0)
    {
        return - other->DifferenceWith(this);
    }

    // (this) >= (other) means other has less or equal length as string
    szDiff = this->Length() - other->Length();
    difference = 0;
    for (int i = 0; i < this->Length(); i++)
    {
        difference *= BASE10;
        if (i >= szDiff)
        {
            difference += this->DigitInPlace(i) - other->DigitInPlace(i - szDiff);
        }
        else
        {
            difference += this->DigitInPlace(i);
        }
    }

    return difference;
}

void DigitString::Print()
{
    std::cout << this->_string;
}