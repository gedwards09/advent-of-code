#include "Solution.h"
#include "FileReader.h"

Solution::Solution(std::string filename)
{
    this->_szContents = FileReader::ReadContentsIntoBuffer(filename, this->_contents, SZ_BUFFER);
}

Solution::Solution(SolutionArgs* args) : Solution(args->Filename()) {  }