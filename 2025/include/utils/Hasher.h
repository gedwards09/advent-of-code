#ifndef __HASHER_H__
#define __HASHER_H__

#include <cstdint>

typedef uint64_t hash_t;

class Hasher
{
    public:
        static hash_t Hash(const unsigned char* p, size_t sz);

    private:
        static const hash_t s_initial = 2166136261;
        static const hash_t s_mult = 16777619;
};

#endif // __HASHER_H__