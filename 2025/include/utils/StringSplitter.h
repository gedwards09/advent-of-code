#ifndef __STRING_SPLITTER_H__
#define __STRING_SPLITTER_H__

#include <string>
#include <vector>

class StringSplitter
{
    public:
        ~StringSplitter() = default;
        StringSplitter();
        static std::vector<std::string> Split(std::string str, char delim);
};
#endif // __STRING_SPLITER_H_