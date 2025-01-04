#include "Monstre.h"

Monstre::Monstre(){};
Monstre::Monstre(std::string nom, int pv, int pm, int attaque, int defence, int vitesse) 
	:Entite{ nom,pv,pm,attaque,defence,vitesse } {}
Monstre::Monstre(const Monstre& monstre) :
	Entite(monstre){}


// a modifier
void Monstre::attaqueDeBase(Entite& cible) {
	cible.altererPv(this->getAttaque());
}
int Monstre::goldLache() {
	return 25; // sera en lien avec le level et stat du monstre // on verra en vrai
}