#pragma once
#include "Equipment.h"
class Casque :
    public Equipment
{
private:
    int pvBonus;
    int pmBonus;
public:

    std::string toString();

    Casque(std::string nom, std::string description, int pvBonus, int pmBonus);
    int getPvBonus();
    int getPmBonus();
};