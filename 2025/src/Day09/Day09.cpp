#include "TileRedecorator.h"

#include "Day09.h"

std::string Day09::SolveEasy()
{
    TileRedecorator tr(this->_contents, this->_szContents);
    return std::to_string(tr.BiggestRectangleArea());
}

std::string Day09::SolveHard()
{
    TileRedecorator tr(this->_contents, this->_szContents);
    return std::to_string(tr.BiggestRectangleWithinArea());
}