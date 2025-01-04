#pragma once
#include "Item.h"
class Armure :
    public Item
{
private:
    int defenceBonus;
public:
    Armure(std::string nom, std::string description, int defenceBonus);
    int getDefenceBonus();
};