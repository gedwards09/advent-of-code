#ifndef __I_HASHABLE_H__
#define __I_HASHABLE_H__

#include <cstdint>

typedef uint64_t hash_t;

class IHashable
{
    public:
        virtual ~IHashable() = default;
        virtual hash_t Hash() = 0;
};

#endif // __I_HASHABLE_H__