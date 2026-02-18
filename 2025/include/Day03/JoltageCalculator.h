#ifndef __JOLTAGE_CALCULATOR_H__
#define __JOLTAGE_CALCULATOR_H__

#include <string>
#include <stdexcept>

#define SAFE_MAX_DIGITS (2)
#define MEGA_MAX_DIGITS (12)
#ifndef BASE10
#define BASE10 (10)
#endif // BASE10

class JoltageCalculator
{
    public:
        static long long TotalJoltage(std::string lines[], int szLines);
        static long long TotalJoltage(std::string lines[], int szLines, bool safety);
        static int MaxJoltage(std::string digitString);
        static long long MegaMaxJoltage(std::string digitString);
    
    private:
        static int charToDigit(char c);
        static bool isDigit(char c);
        static void initDigits(int digits[], const int szDigits);
        static void updateDigits(int digits[], const int szDigits, const char curChar, const int remainingCharCount);
        static void resetDigitsFromIndex(int digits[], const int szDigits, const int idx);
        static long long arrayToLongLong(const int digits[], int szDigits);
        static void print(const int digits[], const int szDigits);
};

#endif // __JOLTAGE_CALCULATOR_H__