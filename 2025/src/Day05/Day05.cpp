#include "IngredientInventory.h"

#include "Day05.h"

std::string Day05::SolveEasy()
{
    IngredientInventory inventory(this->_contents, this->_szContents);
    return std::to_string(inventory.CountIngredients());
}

std::string Day05::SolveHard()
{
    IngredientInventory inventory(this->_contents, this->_szContents);
    return std::to_string(inventory.CountEntireRange());
}