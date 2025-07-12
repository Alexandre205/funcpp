#pragma once
#include "Equipment.h"
class Botte :
    public Equipment
{
private:
    int vitesseBonus;
public:

    std::string toString();

    Botte(std::string nom, std::string description, int vitesseBonus);
    int getVitesseBonus();
};