#ifndef __I_SOLUTION_H__
#define __I_SOLUTION_H__

#include <string>

class ISolution
{
    public:
        virtual ~ISolution() = default;
        virtual std::string SolveEasy() = 0;
        virtual std::string SolveHard() = 0;
};

#endif // __I_SOLUTION_H__