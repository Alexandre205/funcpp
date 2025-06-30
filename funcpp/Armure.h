#pragma once
#include "Equipment.h"
class Armure :
    public Equipment
{
private:
    int defenceBonus;
public:

    std::string toString();

    Armure(std::string nom, std::string description, int defenceBonus);
    int getDefenceBonus();
};