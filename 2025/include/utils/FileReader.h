#ifndef __FILE_READER_H__
#define __FILE_READER_H__

class FileReader
{
    public:
        static size_t ReadContentsIntoBuffer(const std::string filename, std::string buffer[], const size_t szBuffer);
};

#endif // __FILE_READER_H__