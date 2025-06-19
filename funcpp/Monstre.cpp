#include "Monstre.h"
#include "Fight.h"
#include"Utilitaire.h"

std::string Monstre::toString() {
	return getNom() + " (" + std::to_string(pv) + "/" + std::to_string(getPvMax()) + "pv)";
}

Monstre::Monstre(){};
Monstre::Monstre(std::string nom, int pv, int pm, int attaque, int defence, int vitesse) 
	:Entite{ nom,pv,pm,attaque,defence,vitesse } {}
Monstre::Monstre(const Monstre& monstre) :
	Entite(monstre){}


// obsolete
void Monstre::attaqueDeBase(Entite& cible) {
	cible.altererPv(this->getAttaque());
}
int Monstre::goldLache() {
	return 25; // sera en lien avec le level et stat du monstre // on verra en vrai
}
ActionPerforme Monstre::getAction(Perso& joueur, std::vector<Monstre*> monstres) {
	ActionPerforme action{ this };
	Competence* cp{ this->getCompetence(Utilitaire::getRandomInteger(this->nbCompetence-1)) };
	if (cp->getCoutPm() > this->getPm()) {
		// en 0 se trouve l'attaque de base
		cp = this->getCompetence(0);
	}
	action.action = cp;
	action.cibles = std::vector<Entite*>{ &joueur };
	return action;
}