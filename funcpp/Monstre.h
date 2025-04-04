#pragma once
#include "Entite.h"
#include"Item.h"
#include<vector>
class Monstre :
    public Entite
{
private:
    //Race
    struct Loot
    {
        Item objet;
        int pourcentageDeDrop;
    };
    std::vector<struct Loot> objetsLootable;
public:
    Monstre();
    Monstre(const Monstre& monstre);
    Monstre(std::string nom, int pv, int pm, int attaque, int defence, int vitesse);

    void attaqueDeBase(Entite& cible);
    int goldLache();

    // faire un bon truc comme algorithme une fois le systeme de combat amélioré
    ActionPerforme getAction(Perso& joueur, std::vector<Monstre*> monstres);
};