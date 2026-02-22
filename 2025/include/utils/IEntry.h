#ifndef __I_ENTRY_H__
#define __I_ENTRY_H__

template <typename K, typename V>
class IEntry
{
    public:
        virtual ~IEntry() = default;
        virtual K* Key() = 0;
        virtual V* Value() = 0;
        virtual void SetKey(K* key) = 0;
        virtual void SetValue(V* value) = 0;
};

#endif // __I_ENTRY_H__