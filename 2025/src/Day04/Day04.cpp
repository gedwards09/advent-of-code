#include "PaperRollMap.h"

#include "Day04.h"

std::string Day04::SolveEasy()
{
    PaperRollMap map(this->_contents, this->_szContents);
    return std::to_string(map.CountAccessibleRolls());
}

std::string Day04::SolveHard()
{
    PaperRollMap map(this->_contents, this->_szContents);
    return std::to_string(map.CountAllAccessibleRolls());
}


