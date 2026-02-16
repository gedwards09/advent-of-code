#include "SolutionArgs.h"

SolutionArgs::SolutionArgs(std::string filename) : _filename(filename) {  }

std::string SolutionArgs::Filename()
{
    return _filename;
}