#pragma once
#include "Item.h"
class Casque :
    public Item
{
private:
    int pvBonus;
    int pmBonus;
public:
    Casque(std::string nom, std::string description, int pvBonus, int pmBonus);
    int getPvBonus();
    int getPmBonus();
};