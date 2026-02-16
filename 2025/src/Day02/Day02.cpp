#include "RepeatIDValidator.h"

#include "Day02.h"

std::string Day02::SolveEasy()
{
    std::string line;
    RepeatIDValidator validator;
    long long count;

    line = this->_contents[0];
    count = validator.SumInvalidIDs(line);

    return std::to_string(count);
}

std::string Day02::SolveHard()
{
    std::string line;
    RepeatIDValidator validator;
    long long count;

    line = this->_contents[0];
    count = validator.SumMultiInvalidIDs(line);

    return std::to_string(count);
}