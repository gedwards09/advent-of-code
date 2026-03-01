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
    switch (type)
    {
        case 1:
            return new Day01(filename);
        case 2:
            return new Day02(filename);
        case 3:
            return new Day03(filename);
        case 4:
            return new Day04(filename);
        case 5:
            return new Day05(filename);
        case 6:
            return new Day06(filename);
        case 7:
            return new Day07(filename);
        case 8:
            return new Day08(filename);
        default:
            throw std::runtime_error("SolutionFactory.cpp:Option not implemented\n");
    }
}