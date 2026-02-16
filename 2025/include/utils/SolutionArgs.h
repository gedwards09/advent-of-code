#ifndef __SOLUTION_ARGS_H__
#define __SOLUTION_ARGS_H__

#include <string>

class SolutionArgs
{
    public:
        SolutionArgs(std::string filename);
        std::string Filename();

    private:
        std::string _filename;
};

#endif // __SOLUTION_ARGS_H__