#ifndef __HASHABLE_INTEGER_H__
#define __HASHABLE_INTEGER_H__

#include "Hasher.h"
#include "IHashable.h"
#include "Integer.h"

class HashableInteger : public Integer, public IHashable
{
    public:
        HashableInteger(int value);
        virtual hash_t Hash() const override;

    private:
        hash_t _hash;
};

#endif // __HASHABLE_INTEGER_H__