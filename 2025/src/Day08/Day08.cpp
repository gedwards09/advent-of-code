#include "JunctionConnector.h"

#include "Day08.h"

std::string Day08::SolveEasy()
{
    JunctionConnector j(this->_contents, this->_szContents);
    return std::to_string(j.SolveLargestCircuits());
}

std::string Day08::SolveHard()
{
    JunctionConnector j(this->_contents, this->_szContents);
    return std::to_string(j.SolveConnectedCircuit());
}