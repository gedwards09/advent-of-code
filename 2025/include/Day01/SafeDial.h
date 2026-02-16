#ifndef __SAFE_DIAL_H__
#define __SAFE_DIAL_H__

#include <string>
#include "Array.h"

#define SZ_DIAL (100)

class SafeDial
{
    public:
        ~SafeDial();
        SafeDial();
        SafeDial(std::string* contents, int szContents);
        int Count();
        int CountPasses();

    private:
        Array<int>* _array;

};

#endif // __SAFE_DIAL_H__