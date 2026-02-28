#include "Day07.h"

#include "TachMap.h"
#include "QuantumTachMap.h"

std::string Day07::SolveEasy()
{
    TachMap t(this->_contents, this->_szContents);
    return std::to_string(t.CountBeamSplits());
}

std::string Day07::SolveHard()
{
    QuantumTachMap qt(this->_contents, this->_szContents);
    return std::to_string(qt.CountBeamSplits());
}