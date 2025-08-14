#pragma once
#include "Entite.h"
#include"Inventaire.h"
class Perso :
    public Entite
{
private:
    int nbGold;
    Inventaire inventaire;
public:
    std::string toString();

    Perso(std::string nom, std::array<int, NB_STAT> stats);
    //Perso(std::string nom, std::array<int, NB_STAT> stats,int nbGold);


    Inventaire* getInventaire();

    int getPvMax();
    int getPmMax();
    int getAttaque();
    //int getAttaqueMagique();
    int getDefence();
    //int getDefenceMagique();
    int getVitesse();

    int getNbGold();
    void modifyNbGold(int modifier);

    //ici lanceur et joueur sont égaux
    ActionPerforme getAction(Perso& joueur, std::vector<Monstre>& monstres);

    void changerEquipement(Casque nouvCasque);
    void changerEquipement(Arme nouvArme);
    void changerEquipement(Armure nouvArmure);
    void changerEquipement(Botte nouvBotte);

    void addConsumable(Consommable* nouvConso);
};