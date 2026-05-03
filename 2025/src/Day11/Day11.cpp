#include "Network.h"
#include "FFTNetwork.h"

#include "Day11.h"

std::string Day11::SolveEasy()
{
    Network n(this->_contents, this->_szContents);
    return std::to_string(n.Solve());
}

std::string Day11::SolveHard()
{
    Network n(this->_contents, this->_szContents);
    return std::to_string(n.SolveComplex());
}