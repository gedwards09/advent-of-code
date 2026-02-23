#ifndef __INGREDIENT_INVENTORY_H__
#define __INGREDIENT_INVENTORY_H__

#include "Array.h"
#include "Range.h"

class IngredientInventory
{
    public:
        IngredientInventory(std::string contents[], size_t szContents);
        int CountIngredients();
        long long CountEntireRange();

    private:
        Array<Range>* _ranges;
        Array<DigitString>* _ids;
};

#endif // __INGREDIENT_INVENTORY_H__