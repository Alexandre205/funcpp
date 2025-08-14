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

    //constructeur sans gold
    Perso(std::string nom, int pv, int pm, int attaque, int attaqueMagique, int defence, int defenceMagique, int vitesse);

    //constructeur de base
    Perso(std::string nom, int pv, int pm, int attaque, int attaqueMagique, int defence, int defenceMagique, int vitesse,int nbGold);

    //obsolete
    void attaqueDeBase(Entite& cible);

    Inventaire* getInventaire();

    int getPvMax();
    int getPmMax();
    int getAttaque();
    int getDefence();
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