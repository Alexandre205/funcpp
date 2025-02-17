#pragma once
#include "Item.h"
class Armure :
    public Item
{
private:
    int defenceBonus;
public:

    std::string toString();

    Armure(std::string nom, std::string description, int defenceBonus);
    int getDefenceBonus();
};