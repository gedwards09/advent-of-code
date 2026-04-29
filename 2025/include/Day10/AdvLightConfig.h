#ifndef __ADV_LIGHT_CONFIG_H__
#define __ADV_LIGHT_CONFIG_H__

#include "IntegerTableau.h"
#include "LightConfig.h"

#define MAX_BUTTON_COUNT (16)
#define ADV_MAX_STEPS (256)
#define SZ_JOLTAGE_ARR (16)

class AdvLightConfig : public LightConfig
{
    public:
        ~AdvLightConfig();
        AdvLightConfig();

    protected:
        virtual void ClearButtonArray() override;
        virtual void AppendButtonToArray(uint16_t value) override;
        virtual void ClearJoltageArray() override;
        virtual void AppendJoltageToArray(uint8_t value) override;
        virtual int Search() override;
        IntegerTableau* ConstructMatrix();

    private:
        size_t _szButtonArray = 0;
        uint16_t _buttonArray[MAX_BUTTON_COUNT];
        size_t _szJoltageArray = 0;
        uint8_t _joltageArray[SZ_JOLTAGE_ARR];
        int* _intArray[ADV_MAX_STEPS];
        uint8_t _maxButtonLen = 0;


        void initButtonArray();
        void initJoltageArray();
        int* getInt(int i);

};

#endif // __ADV_LIGHT_CONFIG_H__