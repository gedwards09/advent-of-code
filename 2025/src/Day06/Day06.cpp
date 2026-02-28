#include "CephalopodMath.h"

#include "Day06.h"

std::string Day06::SolveEasy()
{
    CephalopodMath c;
    long long out;

    out = c.ColumnSolve(this->_contents, this->_szContents);
    return std::to_string(out);
}

std::string Day06::SolveHard()
{
    long long out;

    out = CephalopodMath::CephalopodSolve(this->_contents, this->_szContents);
    return std::to_string(out);
}