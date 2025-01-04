#pragma once
#include<functional>
#include "Consommable.h"
class Potion :
    public Consommable
{
private:
    std::function<void(Entite&, int)> effet;
    int puissance;
public:
    Potion(std::string nom, std::string description, std::function<void(Entite&, int)> effet, int puissance);
    void utilisation(Entite& cible);
};