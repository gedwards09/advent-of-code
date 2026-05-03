#ifndef __HASHABLE_STRING_H__
#define __HASHABLE_STRING_H__

#include <string>

#include "IHashable.h"

class HashableString : public IHashable
{
    public:
        HashableString(std::string str);
        HashableString(const char* pStr, size_t szStr);
        const char* String() const;
        hash_t Hash() const;
        HashableString* Copy() const;

    private:
        const size_t _szStr;
        const char* _pStr;
        const hash_t _hash;

        HashableString(const char* pStr, size_t szStr, hash_t hash);
};

#endif // __HASHABLE_STRING_H__