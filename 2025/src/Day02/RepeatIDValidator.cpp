#include <stdexcept>

#include "RepeatIDValidator.h"

// public
long long RepeatIDValidator::SumInvalidIDs(std::string rawString)
{
    std::vector<std::string> ranges;
    std::vector<std::string> bounds;
    std::string lowerBoundStr;
    std::string upperBoundStr;
    long long count;

    ranges = RepeatIDValidator::splitRanges(rawString);
    count = 0;
    for (const std::string& range : ranges)
    {
        bounds = RepeatIDValidator::splitBounds(range);
        lowerBoundStr = bounds[0];
        upperBoundStr = bounds[1];
        count += RepeatIDValidator::sumInvalidIDs(lowerBoundStr, upperBoundStr);
    }

    return count;
}

std::vector<std::string> RepeatIDValidator::splitRanges(std::string rawString)
{
    return StringSplitter::Split(rawString, RepeatIDValidator::s_rangeDelim);
}

std::vector<std::string> RepeatIDValidator::splitBounds(std::string rawString)
{
    return StringSplitter::Split(rawString, RepeatIDValidator::s_boundDelim);
}

long long RepeatIDValidator::sumInvalidIDs(std::string lowerBoundStr, std::string upperBoundStr)
{
    return RepeatIDValidator::sumRepeatInvalidIDs(lowerBoundStr, upperBoundStr, 2);
}

long long RepeatIDValidator::sumRepeatInvalidIDs(std::string  lowerBoundStr, std::string upperBoundStr, int repeatTimes)
{
    int lowerBound;
    int upperBound;
    long long count;

    lowerBound = RepeatIDValidator::findFirstRepeatInvalidIDFrom(lowerBoundStr, repeatTimes);
    upperBound = RepeatIDValidator::findLastRepeatInvalidIDFrom(upperBoundStr, repeatTimes);
    count = 0;

    if (lowerBound <= upperBound)
    {
        for (int i = lowerBound; i <= upperBound; i++)
        {
            count += RepeatIDValidator::repeatBase10DigitStringValue(i, repeatTimes);
        }
    }

    return count;
}

int RepeatIDValidator::findFirstRepeatInvalidIDFrom(std::string boundStr, int times)
{
    return RepeatIDValidator::nextRepeatInvalidID(boundStr, times, 1);
}

int RepeatIDValidator::findLastRepeatInvalidIDFrom(std::string boundStr, int times)
{
    return RepeatIDValidator::nextRepeatInvalidID(boundStr, times, -1);
}

int RepeatIDValidator::nextRepeatInvalidID(std::string boundStr, int times, int dir)
{
    int len;
    int repeatLen;
    int topSigDigitValue;
    int digitValue;
    int offset;

    if (times < 2)
    {
        throw std::runtime_error("RepeatIDValidator.cpp:Invalid repeat digit times\n");
    }

    len = boundStr.length();
    repeatLen = (len + times - 1) / times;

    if (len % times != 0)
    {
        if (dir > 0)
        {
            offset = 0;
        }
        else
        {
            offset = -1;
        }

        return RepeatIDValidator::power10Int(repeatLen - 1) + offset;
    }

    topSigDigitValue = std::atoi(boundStr.substr(0, repeatLen).c_str());
    offset = 0;
    for (int i = 1; i < times; i++)
    {
        digitValue = std::atoi(boundStr.substr(i * repeatLen, repeatLen).c_str());
        if (topSigDigitValue == digitValue)
        {
            continue;
        }

        if (topSigDigitValue < digitValue && dir > 0)
        {
            offset = 1;
        }
        else if (topSigDigitValue > digitValue && dir < 0)
        {
            offset = -1;
        }
        
        break;
    }

    return topSigDigitValue + offset;
}

int RepeatIDValidator::power10Int(int exp)
{
    int value;

    // can't express negative exponent as integer
    if (exp < 0)
    {
        return -1;
    }

    value = 1;
    while (exp > 0)
    {
        value *= BASE10;
        exp--;
    }

    return value;
}

long long RepeatIDValidator::repeatBase10DigitStringValue(int value, int times)
{
    long long m;
    long long out;

    if (RepeatIDValidator::base10StringValueHasLowerRepeatSubpattern(value, times))
    {
        // don't return value if it has a lower repeat subpattern
        return 0;
    }

    m = RepeatIDValidator::repeatMultiplier(value);
    out = value;
    while (times > 1)
    {
        out *= m;
        out += value;
        times--;
    }

    return out;
}

bool RepeatIDValidator::base10StringValueHasLowerRepeatSubpattern(int value, int repeatTimes)
{
    int lcm;
    int h;
    long long m;
    int strlen;

    // nothing to check
    if (repeatTimes < 3)
    {
        return false;
    }
    
    strlen = RepeatIDValidator::base10StringLength(value);

    lcm = 1;
    for (int i = 2; i < repeatTimes; i++)
    {
        if (RepeatIDValidator::gcd(lcm, i) != 1)
        {
            continue;
        }

        if (strlen % i != 0)
        {
            continue;
        }

        h = strlen / i;

        // quick detection of repeated digit string of the specified length
        m = RepeatIDValidator::power10Int(h) + 1;
        if (value % m == 0)
        {
            return true;
        }

        lcm *= i;
    }

    return false;
}

int RepeatIDValidator::base10StringLength(int value)
{
    long long m;
    int strlen;

    m = BASE10;
    strlen = 1;
    while (m < value)
    {
        m *= BASE10;
        strlen++;
    }

    return strlen;
}

int RepeatIDValidator::gcd(int a, int b)
{
    int r;

    if (b > a)
    {
        return RepeatIDValidator::gcd(b, a);
    }
    
    r = a % b;
    if (r == 0)
    {
        return b;
    }

    return RepeatIDValidator::gcd(b, r);
}

long long RepeatIDValidator::repeatMultiplier(int value)
{
    long long m;

    m = BASE10;
    while (m <= value)
    {
        m *= BASE10;
    }

    return m;
}

// public
long long RepeatIDValidator::SumMultiInvalidIDs(std::string rawString)
{
    std::vector<std::string> ranges;
    std::vector<std::string> bounds;
    std::string lowerBoundStr;
    std::string upperBoundStr;
    long long count;

    ranges = RepeatIDValidator::splitRanges(rawString);
    count = 0;
    for (const std::string& range : ranges)
    {
        bounds = RepeatIDValidator::splitBounds(range);
        lowerBoundStr = bounds[0];
        upperBoundStr = bounds[1];
        count += RepeatIDValidator::sumMultiInvalidIDs(lowerBoundStr, upperBoundStr);
    }

    return count;
}

long long RepeatIDValidator::sumMultiInvalidIDs(std::string lowerBoundStr, std::string upperBoundStr)
{
    int len;
    int lcm;
    long long count;
    int repeatTimes;

    len = upperBoundStr.length();
    lcm = 1;
    count = 0;
    for (int i = 2; i <= len; i++)
    {
        // only need to check lengths coprime to what we've already checked
        if (RepeatIDValidator::gcd(lcm, i) != 1)
        {
            continue;
        }

        repeatTimes = i;
        count += RepeatIDValidator::sumRepeatInvalidIDs(lowerBoundStr, upperBoundStr, repeatTimes);

        // remember prime factors that we've already checked
        lcm *= i;
    }
    return count;
}