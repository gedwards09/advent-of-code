#ifndef __LIGHT_CONFIG_H__
#define __LIGHT_CONFIG_H__

#include <cstdint>
#include <string>

#include "Array.h"
#include "HashableInteger.h"

#define MAX_INT_KEY (1024)
#define MAX_BUTTON_PRESS (16)
#define START_NUM (0)
#define START_STEPS (0)
#define MAX_JOLTAGE_SZ (16)

class LightConfig
{
    public:
        ~LightConfig();
        LightConfig();
        int SolveAll(std::string contents[], size_t szContents);
        virtual int Solve(std::string line);

    protected:
        static void InitArray(void** ppArr, size_t sz);
        static size_t ReadTargetValue(int* pTarget, const char* pStr, size_t szStr, size_t idx);
        static size_t ReadWhitespace(const char* pStr, size_t szStr, size_t idx);
        size_t ReadButtonsIntoArray(const char* pStr, size_t szStr, size_t idx);
        virtual void ClearButtonArray();
        virtual void AppendButtonToArray(uint16_t value);
        static size_t ReadButton(int* pValue, const char* pStr, size_t szStr, size_t idx);
        size_t ReadJoltageIntoArray(const char* pStr, size_t szStr, size_t idx);
        virtual void ClearJoltageArray();
        static size_t ReadJoltage(uint8_t* pValue, const char* pStr, size_t szStr, size_t idx);
        virtual void AppendJoltageToArray(uint8_t value);
        virtual int Search();

    private:
        static const char s_space = ' ';
        static const char s_lightOn = '#';
        static const char s_startButton = '(';
        static const char s_endButton = ')';
        static const char s_digitSep = ',';
        static const char s_zero = '0';
        static const char s_nine = '9';
        static const char s_startConfig = '[';
        static const char s_endConfig = ']';
        static const char s_startJoltage = '{';
        static const char s_endJoltage = '}';

        int _target;
        Array<HashableInteger>* _buttonArray;
        HashableInteger* _hashKeyArray[MAX_INT_KEY];
        int* _intArray[MAX_BUTTON_PRESS];

        int bfs(int target, Array<HashableInteger>* pArray);
        HashableInteger* getHashableInteger(int i);
        int* getInt(int i);
};

#endif // __LIGHT_CONFIG_H__