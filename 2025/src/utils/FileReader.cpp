#include <fstream>
#include <iostream>

#include "FileReader.h"

size_t FileReader::ReadContentsIntoBuffer(const std::string filename, std::string buffer[], const size_t szBuffer)
{
    std::ifstream file(filename);
    std::string str;
    size_t szContents;

    if (!file || !file.is_open())
    {
        throw std::runtime_error("FileReader.cpp: File could not be opened");
    }
    
    szContents = 0;
    while (szContents < szBuffer)
    {
        if (!(std::getline(file, str)))
        {
            break;
        }
        buffer[szContents] = str;
        szContents++;
    }

    if (szContents == szBuffer && std::getline(file, str))
    {
        std::cout << "FileReader.cpp:Warning:File contents exceeded buffer size" << std::endl;
    }

    return szContents;
}