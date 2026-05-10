#include "GiftPacking.h"

#include "Day12.h"

std::string Day12::SolveEasy()
{
    GiftPacking g(this->_contents, this->_szContents);
    return std::to_string(g.Solve());
}

std::string Day12::SolveHard()
{
    // no day 12 hard solution
    return 0;
}