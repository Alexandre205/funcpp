#pragma once
#include "Entite.h"
#include"ILootable.h"
#include<vector>
class Monstre :
    public Entite
{
private:
    //Race
    int goldRecompense;
    struct Loot
    {
        ILootable objet;
        int pourcentageDeDrop;
    };
    //std::vector<struct Loot> objetsLootable;
public:
    std::string toString();
    Monstre(const Monstre& monstre);
    Monstre(std::string nom, std::array<int, NB_STAT> stats, int goldRecompense);
    int goldLache();

    // faire un bon truc comme algorithme une fois le systeme de combat amélioré
    ActionPerforme getAction(Perso& joueur, std::vector<Monstre>& monstres);
};