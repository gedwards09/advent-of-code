#include "Day09.h"

Day09::~Day09()
{
    if (this->_ptr == NULL)
    {
        delete this->_ptr;
        this->_ptr = NULL;
    }
}

Day09::Day09(std::string filename) : Solution(filename) {  }

std::string Day09::SolveEasy()
{
    this->_ptr = new TileRedecorator(this->_contents, this->_szContents);
    return std::to_string(this->_ptr->BiggestRectangleArea());
}

std::string Day09::SolveHard()
{
    if (this->_ptr == NULL)
    {
        this->_ptr = new TileRedecorator(this->_contents, this->_szContents);
    }
    return std::to_string(this->_ptr->BiggestRectangleWithinArea());
}