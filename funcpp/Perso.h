#pragma once
#include "Entite.h"
#include"Inventaire.h"
class Perso :
    public Entite
{
private:
    int nbGold;
    //Classe classe
    Inventaire inventaire;
public:
    std::string toString();
    Perso(std::string nom, int pv, int pm, int attaque, int defence, int vitesse);
    Perso(std::string nom, int pv, int pm, int attaque, int defence, int vitesse,int nbGold);

    //obsolete
    void attaqueDeBase(Entite& cible);

    Inventaire* getInventaire();

    int getPvMax();
    int getPmMax();
    int getAttaque();
    int getDefence();
    int getVitesse();

    //ici lanceur et joueur sont égaux
    ActionPerforme getAction(Perso& joueur, std::vector<Monstre*> monstres);

    void changerEquipement(Casque nouvCasque);
    void changerEquipement(Arme nouvArme);
    void changerEquipement(Armure nouvArmure);
    void changerEquipement(Botte nouvBotte);
};