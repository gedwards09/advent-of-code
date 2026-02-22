#ifndef __HASH_TABLE_ENTRY_H__
#define __HASH_TABLE_ENTRY_H__

#include <concepts>

#include "Entry.h"
#include "IHashable.h"

template <typename K, typename V>
requires std::derived_from<K, IHashable>
class HashTableEntry : public Entry<K,V>
{
    public:
        using Entry<K,V>::Entry;
};

#endif // __HASH_TABLE_ENTRY_H__