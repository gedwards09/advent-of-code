#include "LightConfig.h"

#include "Day10.h"

std::string Day10::SolveEasy()
{
    LightConfig lc;
    return std::to_string(lc.SolveAll(this->_contents, this->_szContents));
}

std::string Day10::SolveHard()
{
    return "";
}