#ifndef __ENTRY_H__
#define __ENTRY_H__

#include "IEntry.h"

template <typename K, typename V>
class Entry : public IEntry<K,V>
{
    public:
        virtual ~Entry() override;
        Entry();
        Entry(K* key, V* value);
        virtual K* Key() override;
        virtual V* Value() override;
        virtual void SetKey(K* key) override;
        virtual void SetValue(V* value) override;

    private:
        K* _key;
        V* _value;
};

template <typename K, typename V>
Entry<K,V>::Entry(K* key, V* value) : _key(key), _value(value) {  }

template <typename K, typename V>
Entry<K,V>::Entry() : Entry(NULL, NULL) {  }

template <typename K, typename V>
Entry<K,V>::~Entry()
{
    delete this->_value;
    this->_value = NULL;
    delete this->_key;
    this->_key = NULL;
}

template <typename K, typename V>
K* Entry<K,V>::Key()
{
    return this->_key;
}

template <typename K, typename V>
V* Entry<K,V>::Value()
{
    return this->_value;
}

template <typename K, typename V>
void Entry<K,V>::SetKey(K* key)
{
    this->_key = key;
}

template <typename K, typename V>
void Entry<K,V>::SetValue(V* value)
{
    this->_value = value;
}

#endif // __ENTRY_H__