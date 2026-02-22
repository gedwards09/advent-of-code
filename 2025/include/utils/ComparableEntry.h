#ifndef __COMPARABLE_ENTRY_H__
#define __COMPARABLE_ENTRY_H__

#include <cassert>
#include <concepts>

#include "Entry.h"
#include "IComparable.h"

template <typename K, typename V, typename W = V>
requires std::derived_from<V, W> && std::derived_from<V, IComparable<W>>
class ComparableEntry : public Entry<K,V>, public IComparable<Entry<K,V>>
{
    public:
        using Entry<K,V>::Entry;
        virtual int CompareTo(Entry<K,V>* other) override;
};

template <typename K, typename V, typename W>
requires std::derived_from<V, W> && std::derived_from<V, IComparable<W>>
int ComparableEntry<K, V, W>::CompareTo(Entry<K,V>* other)
{
    assert(this->Value() != NULL && other->Value() != NULL);
    return this->Value()->CompareTo(other->Value());
}

#endif // __COMPARABLE_ENTRY_H__