#include <string>
#include <sstream>
#include <vector>

#include "StringSplitter.h"

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

std::string StringSplitter::Piece(std::string str, char delim, size_t piece)
{
    std::vector<std::string> pieces;

    pieces = StringSplitter::Split(str, delim);
    if (piece < pieces.size())
    {
        return pieces[piece];
    }
    else
    {
        return std::string("");
    }
}