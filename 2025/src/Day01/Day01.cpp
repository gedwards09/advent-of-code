#include <string>
#include "SafeDial.h"

#include "Day01.h"

std::string Day01::SolveEasy()
{
    SafeDial dial(this->_contents, this->_szContents);
    return std::to_string(dial.Count());
}

std::string Day01::SolveHard()
{
    SafeDial dial(this->_contents, this->_szContents);
    return std::to_string(dial.CountPasses());
}