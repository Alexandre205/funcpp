#include "Perso.h"
#include "Fight.h"
#include "InputConsole.h"

std::string Perso::toString() {
	std::string retour =  Entite::toString() + "(" + std::to_string(nbGold) + " gold)\n";
	retour += inventaire.toString();
	return retour;
}

Perso::Perso(std::string nom, int pv, int pm, int attaque, int defence, int vitesse,int nbGold) :
	Entite{nom,pv,pm,attaque,defence,vitesse},nbGold{nbGold}{
	// ceci appel le constructeur par defaut de l'inventaire
}
Perso::Perso(std::string nom, int pv, int pm, int attaque, int defence, int vitesse) 
	:Perso{ nom,pv,pm,attaque,defence,vitesse,0 } {}


// a supprimer //peut-etre //surement
void Perso::attaqueDeBase(Entite& cible) {
	int degatInflige = getAttaque() - cible.getDefence();
	cible.altererPv(degatInflige>=1?degatInflige:1);
}

Inventaire* Perso::getInventaire() {
	return &inventaire;
}

int Perso::getPvMax() {
	int test = pvMax + inventaire.getCasque().getPvBonus();
	return test <= STAT_MAX_EFFECTIVE ? test : STAT_MAX_EFFECTIVE;
}
int Perso::getPmMax(){
	int test = pmMax + inventaire.getCasque().getPmBonus();
	return test <= STAT_MAX_EFFECTIVE ? test : STAT_MAX_EFFECTIVE;
}
int Perso::getAttaque() {
	int test = attaque + inventaire.getArme().getAttaqueBonus();
	return test <= STAT_MAX_EFFECTIVE ? test : STAT_MAX_EFFECTIVE;
}
int Perso::getDefence() {
	int test = defence + inventaire.getArmure().getDefenceBonus();
	return test <= STAT_MAX_EFFECTIVE ? test : STAT_MAX_EFFECTIVE;
}
int Perso::getVitesse() {
	int test = vitesse + inventaire.getBotte().getVitesseBonus();
	return test <= STAT_MAX_EFFECTIVE ? test : STAT_MAX_EFFECTIVE;
}
int Perso::getNbGold() {
	return nbGold;
}
void Perso::modifyNbGold(int modifier) {
	nbGold += modifier; //faire attention ici les gold peuvent etre négatif
}

ActionPerforme Perso::getAction(Perso& joueur, std::vector<Monstre>& monstres) {
	std::vector<Entite*> ennemis;
	//ennemis.reserve();
	for (int i{ 0 }; i < monstres.size(); i++) {
		ennemis.push_back(&monstres[i]);
	}
	return Obtention::getActionPerforme(*this, ennemis);
}

// plus complexe car gestion pv
void Perso::changerEquipement(Casque nouvCasque) {
	getInventaire()->ajouterEquipement(nouvCasque);
	if (pv > getPvMax()) {
		pv = getPvMax();
	}
	if (pm > getPmMax()) {
		pm = getPmMax();
	}
}
void Perso::changerEquipement(Arme nouvArme) {
	getInventaire()->ajouterEquipement(nouvArme);
}
void Perso::changerEquipement(Armure nouvArmure) {
	getInventaire()->ajouterEquipement(nouvArmure);
}
void Perso::changerEquipement(Botte nouvBotte) {
	getInventaire()->ajouterEquipement(nouvBotte);
}

void Perso::addConsumable(Consommable* nouvConso) {
	nouvConso->ajouterPossesseur(this);
	inventaire.ajouterConsommable(nouvConso);
}