#include <cassert>

#include "Integer.h"

Integer::Integer() : Integer(0) {  }

Integer::Integer(int value) : Value(value) {  }

Integer::Integer(int* pValue) : Integer(Integer::Deref(pValue)) {  }

int Integer::Deref(int* pValue)
{
    assert(pValue != NULL);
    return *pValue;
}

int Integer::CompareTo(Integer* other) const
{
    return this->Value - other->Value;
}