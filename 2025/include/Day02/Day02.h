#ifndef __DAY_02_H__
#define __DAY_02_H__
#include "Solution.h"
#include "StringSplitter.h"

typedef long long (*fpcounter_t)(std::string lowerBoundStr, std::string upperBoundStr);

class Day02 : public Solution
{
    public:
        using Solution::Solution;
        std::string SolveEasy() override;
        std::string SolveHard() override;
};

#endif // __DAY_02_H__