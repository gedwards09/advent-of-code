#include <iostream>
#include "SafeDial.h"

template class Array<int>;

SafeDial::~SafeDial()
{
    delete _array;
    _array = NULL;
}

SafeDial::SafeDial()
{
    this->_array = new Array<int>();
}

SafeDial::SafeDial(std::string* contents, int szContents) : SafeDial()
{
    std::string line;
    int value;

    for (int i = 0; i < szContents; i++)
    {
        line = contents[i];
        if (line[0] == 'L')
        {
            value = -1 * std::stoi(&line[1]);
        }
        else if (line[0] == 'R')
        {
            value = std::stoi(&line[1]);
        }
        else
        {
            throw std::runtime_error("Day01.cpp:Unrecognized command: " + line + "\n");
        }
        this->_array->Append(value);
    }
}

int SafeDial::Count()
{
    int position;
    int count;

    position = 50;
    count = 0;
    for (int i = 0; i < this->_array->Size(); i++)
    {
        position += this->_array->Get(i);
        if (position % 100 == 0)
        {
            count += 1;
        }
    }

    return count;
}

int SafeDial::CountPasses()
{
    
    int curPosition;
    int curWindingNum;
    int lastPosition;
    int lastWindingNum;
    int count;

    lastPosition = 50;
    lastWindingNum = 0;
    count = 0;
    for (int i = 0; i < this->_array->Size(); i++)
    {
        curPosition = lastPosition + this->_array->Get(i);

        if (curPosition > 0)
        {
            curWindingNum = curPosition / SZ_DIAL;
        }
        else
        {
            curWindingNum = (curPosition - SZ_DIAL + 1) / SZ_DIAL;
        }

        if (this->_array->Get(i) >= 0)
        { 
            count += curWindingNum - lastWindingNum;
        }
        else
        {
            count += lastWindingNum - curWindingNum;

            if (lastPosition % 100 == 0 && curPosition % 100 != 0)
            {
                count--;
            }
            else if (lastPosition % 100 != 0 && curPosition % 100 == 0)
            {
                count++;
            }
        }

        lastWindingNum = curWindingNum;
        lastPosition = curPosition;
    }

    return count;
}