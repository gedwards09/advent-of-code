#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <fstream>
#include <iostream>
#include <string>

#include "ISolution.h"
#include "SolutionArgs.h"

#define SZ_BUFFER (8192)

class Solution : public ISolution
{
    public:
        Solution(SolutionArgs* args);
        Solution(std::string filename);

    protected:
        std::string _contents[SZ_BUFFER];
        size_t _szContents;
};
#endif // __SOLUTION_H__