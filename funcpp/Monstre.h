#pragma once
#include "Entite.h"
#include"Item.h"
#include<map>
class Monstre :
    public Entite
{
private:
    //Race
    //std::map<Item, int> loot;
public:
    Monstre();
    Monstre(const Monstre& monstre);
    Monstre(std::string nom, int pv, int pm, int attaque, int defence, int vitesse);

    void attaqueDeBase(Entite& cible);
    int goldLache();
};