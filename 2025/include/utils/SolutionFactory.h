#ifndef __SOLUTION_FACTORY_H__
#define __SOLUTION_FACTORY_H__

#include "IFactory.h"
#include "ISolution.h"
#include "SolutionArgs.h"

class SolutionFactory : public IFactory<ISolution, SolutionArgs> 
{
    public:
        ISolution* Build(int type, SolutionArgs* args) override;
};

#endif // __SOLUTION_FACTORY_H__