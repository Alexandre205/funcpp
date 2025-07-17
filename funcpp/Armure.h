#pragma once
#include "Equipment.h"
class Armure :
    public Equipment
{
private:
    int defenceBonus;
    int defenceMagiqueBonus;
public:

    std::string toString();

    Armure(std::string nom, std::string description, int defenceBonus, int defenceMagiqueBonus);
    int getDefenceBonus();
    int getDefenceMagiqueBonus();
};