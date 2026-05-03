#ifndef __STRING_SPLITTER_H__
#define __STRING_SPLITTER_H__

#include <string>
#include <vector>

class StringSplitter
{
    public:
        static std::vector<std::string> Split(std::string str, char delim);
        static std::string Piece(std::string str, char delim, char piece);
};

#endif // __STRING_SPLITER_H_