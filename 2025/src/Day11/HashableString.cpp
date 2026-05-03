#include "Hasher.h"

#include "HashableString.h"

HashableString::HashableString(std::string str)
        : HashableString(str.c_str(), str.size()) {  }

HashableString::HashableString(const char* pStr, size_t szStr)
        : HashableString::HashableString(pStr, szStr, Hasher::Hash((unsigned char*)pStr, szStr)) {  }

HashableString::HashableString(const char* pStr, size_t szStr, hash_t hash)
        : _szStr(szStr), _pStr(pStr), _hash(hash) {  }

const char* HashableString::String() const
{
        return this->_pStr;
}

hash_t HashableString::Hash() const
{
    return this->_hash;
}

HashableString* HashableString::Copy() const
{
    return new HashableString(this->_pStr, this->_szStr, this->_hash);
}