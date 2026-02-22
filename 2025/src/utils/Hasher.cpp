#include "Hasher.h"

hash_t Hasher::Hash(const unsigned char* p, size_t sz)
{
    hash_t h = Hasher::s_initial;
    for (size_t i = 0; i < sz; i++)
    {
        h ^= (unsigned char)p[i];
        h *= Hasher::s_mult;
    }

    return h;
}