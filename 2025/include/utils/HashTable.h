#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <cassert>
#include <cstdint>

#include "HashTableEntry.h"

#define MAX_TABLE_LOAD (0.618)
#define DEFAULT_TABLE_CAPACITY (256)

template <typename K, typename V>
requires std::derived_from<K, IHashable>
class HashTable
{
    public:
        ~HashTable();
        HashTable();
        bool Get(K* key, V** value);
        bool Set(K* key, V* value);
        bool Delete(K* key);
        HashTableEntry<K,V>* FindKey(K* key);

    private:
        static V s_deleted;
        int _count;
        int _capacity;
        HashTableEntry<K,V>* _entries;

        void grow();
        static int GrowCapacity(int capacity);
        static HashTableEntry<K,V>* InitEntries(int capacity);
        static HashTableEntry<K,V>* FindKey(
                HashTableEntry<K,V>* table, int capacity, K* key);
};

template <typename K, typename V>
requires std::derived_from<K, IHashable>
V HashTable<K,V>::s_deleted {  };

template <typename K, typename V>
requires std::derived_from<K, IHashable>
HashTable<K,V>::HashTable() : _count(0), _capacity(0), _entries(NULL) {  }

template <typename K, typename V>
requires std::derived_from<K, IHashable>
HashTable<K,V>::~HashTable()
{
    Entry<K,V>* pEntry;

    for (int i = 0; i < this->_capacity; i++)
    {
        pEntry = &this->_entries[i];
        if (pEntry->Value() == (V*)&HashTable<K,V>::s_deleted)
        {
            pEntry->SetValue(NULL);
        }
    }
    delete[] this->_entries;
    this->_entries = NULL;
    this->_capacity = 0;
    this->_count = 0;
}

template <typename K, typename V>
requires std::derived_from<K, IHashable>
bool HashTable<K,V>::Get(K* key, V** value)
{
    HashTableEntry<K,V>* entry;
    
    assert(key != NULL && value != NULL);
    if (this->_count == 0)
    {
        return false;
    }

    entry = FindKey(key);
    assert(entry != NULL);
    if (entry->Key() == NULL)
    {
        return false;
    }

    *value = entry->Value();
    return true;
}

template <typename K, typename V>
requires std::derived_from<K, IHashable>
bool HashTable<K,V>::Set(K* key, V* value)
{
    HashTableEntry<K,V>* pEntry;
    bool isNewKey;

    assert(key != NULL && value != NULL);
    if (this->_count + 1 > this->_capacity * MAX_TABLE_LOAD)
    {
        this->grow();
    }

    pEntry = this->FindKey(key);
    isNewKey = (pEntry->Key() == NULL);
    if (isNewKey && pEntry->Value() == NULL)
    {
        this->_count++;
    }
    else if (!isNewKey)
    {
        if (pEntry->Key() != key)
        {
            delete pEntry->Key();
        }

        if (pEntry->Value() != value)
        {
            delete pEntry->Value();
        } 
    }

    pEntry->SetKey(key);
    pEntry->SetValue(value);
    return isNewKey;
}

template <typename K, typename V>
requires std::derived_from<K, IHashable>
void HashTable<K,V>::grow()
{
    int capacity;
    int count;
    HashTableEntry<K,V>* pEntries;
    HashTableEntry<K, V>* pSource;
    HashTableEntry<K, V>* pDest;

    capacity = HashTable<K,V>::GrowCapacity(this->_capacity);
    pEntries = HashTable<K,V>::InitEntries(capacity);

    count = 0;    
    for (int i = 0; i < this->_capacity; i++)
    {
        pSource = &this->_entries[i];
        if (pSource->Key() == NULL)
        {
            continue;
        }
        pDest = HashTable<K,V>::FindKey(pEntries, capacity, pSource->Key());
        pDest->SetKey(pSource->Key());
        pDest->SetValue(pSource->Value());
        pSource->SetKey(NULL);
        pSource->SetValue(NULL);
        count++;
    }

    delete[] this->_entries;
    this->_entries = pEntries;
    this->_capacity = capacity;
    this->_count = count;
}

// static
template <typename K, typename V>
requires std::derived_from<K, IHashable>
int HashTable<K,V>::GrowCapacity(int capacity)
{
    if (capacity < DEFAULT_TABLE_CAPACITY)
    {
        capacity = DEFAULT_TABLE_CAPACITY;
    }
    else
    {
        capacity *= 2;
    }

    return capacity;
}

//static
template <typename K, typename V>
requires std::derived_from<K, IHashable>
HashTableEntry<K,V>* HashTable<K,V>::InitEntries(int capacity)
{
    HashTableEntry<K,V>* pEntries;
    HashTableEntry<K,V>* pEntry;

    pEntries = new HashTableEntry<K,V>[capacity];
    assert(pEntries != NULL);
    for (int i = 0; i < capacity; i++)
    {
        pEntry = &pEntries[i];
        pEntry->SetKey(NULL);
        pEntry->SetValue(NULL);
    }

    return pEntries;
}

template <typename K, typename V>
requires std::derived_from<K, IHashable>
bool HashTable<K,V>::Delete(K* key)
{
    HashTableEntry<K,V>* pEntry;

    if (this->_count == 0)
    {
        return false;
    }

    pEntry = this->FindKey(key);
    assert(pEntry != NULL);
    if (pEntry->Key() == NULL)
    {
        return false;
    }
    else
    {
        delete pEntry->Key();
        delete pEntry->Value();
        pEntry->SetKey(NULL);
        pEntry->SetValue(&HashTable<K,V>::s_deleted);
        return true;
    }
}

template <typename K, typename V>
requires std::derived_from<K, IHashable>
HashTableEntry<K,V>* HashTable<K,V>::FindKey(K* key)
{
    return HashTable<K,V>::FindKey(this->_entries, this->_capacity, key);
}

// static
template <typename K, typename V>
requires std::derived_from<K, IHashable>
HashTableEntry<K,V>* HashTable<K,V>::FindKey(HashTableEntry<K,V>* entries, int capacity, K* key)
{
    hash_t index;
    hash_t keyHash;
    HashTableEntry<K,V>* deletedEntry;
    HashTableEntry<K,V>* entry;

    keyHash = key->Hash();
    index = keyHash & (capacity - 1);
    deletedEntry = NULL;
    for (int i = 0; i < capacity; i++)
    {
        entry = &entries[index];
        if (entry->Key() == NULL)
        {
            if (entry->Value() == NULL)
            {
                if (deletedEntry != NULL)
                {
                    return deletedEntry;
                }
                else
                {
                    return entry;
                };
            }
            else if (deletedEntry == NULL)
            {
                deletedEntry = entry;
            }
        }
        else if (entry->Key()->Hash() == keyHash)
        {
            return entry;
        }
        index = (index + 1) & (capacity - 1);
    }

    //unreachable
    assert(false);
    return NULL;
}

#endif // __HASH_TABLE_H__