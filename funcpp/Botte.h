#pragma once
#include "Item.h"
class Botte :
    public Item
{
private:
    int vitesseBonus;
public:

    std::string toString();

    Botte(std::string nom, std::string description, int vitesseBonus);
    int getVitesseBonus();
};