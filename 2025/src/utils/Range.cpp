#include <cassert>
#include <iostream>

#include "StringSplitter.h"

#include "Range.h"

Range::~Range()
{
    delete this->_lower;
    this->_lower = NULL;
    delete this->_upper;
    this->_upper = NULL;
}

Range::Range(std::string line) : _lower(NULL), _upper(NULL)
{
    std::vector<std::string> arr;

    arr = StringSplitter::Split(line, Range::s_delim);

    this->_lower = new DigitString(arr[0]);
    this->_upper = new DigitString(arr[1]);
}

DigitString* Range::GetLower()
{
    return this->_lower;
}

DigitString* Range::GetUpper()
{
    return this->_upper;
}

bool Range::InRange(DigitString* d)
{
    return this->_lower->CompareTo(d) <= 0 
            && d->CompareTo(this->_upper) <= 0;
}

void Range::Print()
{
    this->_lower->Print();
    std::cout  << Range::s_delim;
    this->_upper->Print();
}