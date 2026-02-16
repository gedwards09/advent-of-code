#include <string>
#include <sstream>
#include <vector>

#include "StringSplitter.h"

StringSplitter::StringSplitter() {  }

std::vector<std::string> StringSplitter::Split(std::string str, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream stream(str);
    std::string token;

    while (std::getline(stream, token, delim))
    {
        tokens.push_back(token);
    }

    return tokens;
}