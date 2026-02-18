#include <cassert>

#include "JoltageCalculator.h"

#include <iostream>

long long JoltageCalculator::TotalJoltage(std::string lines[], int szLines)
{
    // better turn on safety by default
    return JoltageCalculator::TotalJoltage(lines, szLines, true);
}

long long JoltageCalculator::TotalJoltage(std::string lines[], int szLines, bool safety)
{
    long long count;

    count = 0;
    for (int i = 0; i < szLines; i++)
    {
        if (safety)
        {
            count += JoltageCalculator::MaxJoltage(lines[i]);
        }
        else
        {
            count += JoltageCalculator::MegaMaxJoltage(lines[i]);
        }
    }

    return count;
}

int JoltageCalculator::MaxJoltage(std::string digitString)
{
    int length;
    int digits[SAFE_MAX_DIGITS];
    char curChar;
    int remainingCharCount;

    length = digitString.length();
    JoltageCalculator::initDigits(digits, SAFE_MAX_DIGITS);
    for (int i = 0; i < length; i++)
    {
        curChar = digitString[i];
        remainingCharCount = length - i;
        updateDigits(digits, SAFE_MAX_DIGITS, curChar, remainingCharCount);
    }

    return JoltageCalculator::arrayToLongLong(digits, SAFE_MAX_DIGITS);
}

int JoltageCalculator::charToDigit(char c)
{
    if (!JoltageCalculator::isDigit(c))
    {
        throw std::runtime_error("JoltageCalculate.cpp:Invalid digit\n");
    }
    return (int)(c - '0');
}

bool JoltageCalculator::isDigit(char c)
{
    return '0' <= c && c <= '9';
}

long long JoltageCalculator::MegaMaxJoltage(std::string digitString)
{
    int length;
    int digits[MEGA_MAX_DIGITS];
    char curChar;
    int remainingCharCount;

    length = digitString.length();
    JoltageCalculator::initDigits(digits, MEGA_MAX_DIGITS);
    for (int i = 0; i < length; i++)
    {
        curChar = digitString[i];
        // number of digits remaining including this digit
        remainingCharCount = length - i;
        JoltageCalculator::updateDigits(digits, MEGA_MAX_DIGITS, curChar, remainingCharCount);
    }

    return arrayToLongLong(digits, MEGA_MAX_DIGITS);
}

void JoltageCalculator::initDigits(int digits[], const int szDigits)
{
    JoltageCalculator::resetDigitsFromIndex(digits, szDigits, 0);
}

void JoltageCalculator::resetDigitsFromIndex(int digits[], const int szDigits, const int idx)
{
    assert(0 <= idx && idx <= szDigits);
    for (int i = idx; i < szDigits; i++)
    {
        digits[i] = 0;
    }
}

void JoltageCalculator::updateDigits(int digits[], const int szDigits, const char curChar, const int remainingCharCount)
{
    int currentValue;
    int idx;
    int digitsRemaining;
    int digit;

    currentValue = JoltageCalculator::charToDigit(curChar);
    idx = 0;
    while (idx < szDigits)
    {
        digitsRemaining = szDigits - idx;
        if (digitsRemaining <= remainingCharCount)
        {
            digit = digits[idx];
            if (currentValue > digit)
            {
                digits[idx] = currentValue;
                JoltageCalculator::resetDigitsFromIndex(digits, szDigits, idx + 1);
                return;
            }
        }
        // else skip

        idx++;
    }
}

long long JoltageCalculator::arrayToLongLong(const int digits[], const int szDigits)
{
    long long total;

    total = 0;
    for (int i = 0; i < szDigits; i++)
    {
        total *= 10;
        total += digits[i];
    }
    
    return total;
}

void JoltageCalculator::print(const int digits[], const int szDigits)
{
    std::cout << '\t';
    for (int i = 0; i < szDigits; i++)
    {
        std::cout << (char)(digits[i] + '0');
        if (((szDigits - i) % 3) == 0 && i + 1 < szDigits)
        {
            std::cout << ',';
        }
    }
    std::cout << std::endl;
}