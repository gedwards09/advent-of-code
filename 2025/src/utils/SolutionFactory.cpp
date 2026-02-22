#include <string>

#include "ISolution.h"
#include "SolutionArgs.h"
#include "SolutionFactory.h"
#include "Days.h"

template class IFactory<ISolution, SolutionArgs>;

ISolution* SolutionFactory::Build(int type, SolutionArgs* args)
{
    std::string filename;
    
    filename = args->Filename();
    if (type == 1)
    {
        return new Day01(filename);
    }
    if (type == 2)
    {
        return new Day02(filename);
    }
    if (type == 3)
    {
        return new Day03(filename);
    }
    if (type == 4)
    {
        return new Day04(filename);
    }
    else
    {
        throw std::runtime_error("SolutionFactory.cpp:Option not implemented\n");
    }
}