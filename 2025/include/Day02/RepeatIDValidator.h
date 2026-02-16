#ifndef __REPEAT_ID_VALIDATOR_H__
#define __REPEAT_ID_VALIDATOR_H__

#include <string>
#include <vector>
#include "StringSplitter.h"

#define BASE10 (10)

class RepeatIDValidator
{
    public:
        static long long SumInvalidIDs(std::string rawString);
        static long long SumMultiInvalidIDs(std::string rawString);

    private:
        static const char s_rangeDelim = ',';
        static const char s_boundDelim = '-';
        static const StringSplitter s_splitter;

        static std::vector<std::string> splitRanges(std::string rawString);
        static std::vector<std::string> splitBounds(std::string rawString);
        static long long sumInvalidIDs(
                std::string lowerBoundstr, std::string upperBoundStar);
        static long long sumRepeatInvalidIDs(
                std::string  lowerBoundStr, std::string upperBoundStr, int repeatTimes);
        static int findFirstRepeatInvalidIDFrom(std::string boundStr, int times);
        static int findLastRepeatInvalidIDFrom(std::string boundStr, int times);
        static int nextRepeatInvalidID(std::string boundStr, int times, int dir);
        static int power10Int(int exp);
        static long long repeatBase10DigitStringValue(int value, int times);
        static bool base10StringValueHasLowerRepeatSubpattern(int value, int times);
        static int base10StringLength(int value);
        static int gcd(int a, int b);
        static long long repeatMultiplier(int value);
        static long long sumMultiInvalidIDs(
                std::string lowerBoundstr, std::string upperBoundStar);
};

#endif // __REPEAT_ID_VALIDATOR_H__