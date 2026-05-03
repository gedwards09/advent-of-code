#include "HashableInteger.h"

HashableInteger::HashableInteger(int value) : 
        Integer(value), 
        _hash(Hasher::Hash((const unsigned char*)&value, sizeof(int))) {  }

hash_t HashableInteger::Hash() const
{
    return this->_hash;
}