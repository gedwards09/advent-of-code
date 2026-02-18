#include "JoltageCalculator.h"

#include "Day03.h"

std::string Day03::SolveEasy()
{
    int maxVoltage = JoltageCalculator::TotalJoltage(this->_contents, this->_szContents);
    return std::to_string(maxVoltage);
}

std::string Day03::SolveHard()
{
    long long megaMaxVoltage = JoltageCalculator::TotalJoltage(this->_contents, this->_szContents, false);
    return std::to_string(megaMaxVoltage);
}