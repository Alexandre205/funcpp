#include "Monstre.h"
#include "Fight.h"
#include"Utilitaire.h"

std::string Monstre::toString() {
	return getNom() + " (" + std::to_string(pv) + "/" + std::to_string(getPvMax()) + "pv)";
}


Monstre::Monstre(std::string nom, int pv, int pm, int attaque, int attaqueMagique, int defence, int defenceMagique, int vitesse,int goldRecompense)
	:Entite{ nom,pv,pm,attaque,attaqueMagique,defence,defenceMagique,vitesse }, goldRecompense{goldRecompense} {
}
Monstre::Monstre(const Monstre& monstre) : Monstre(monstre.nom, monstre.pv, monstre.pm, monstre.attaque,monstre.attaqueMagique, monstre.defence,monstre.defenceMagique, monstre.vitesse,monstre.goldRecompense) {
	for (int i{ 0 }; i < monstre.nbCompetence;i++) {
		this->apprendreCompetence(new Competence(monstre.competences[i]));
	}
}


// obsolete
void Monstre::attaqueDeBase(Entite& cible) {
	cible.altererPv(this->getAttaque());
}
int Monstre::goldLache() {
	return goldRecompense;
}
ActionPerforme Monstre::getAction(Perso& joueur, std::vector<Monstre>& monstres) {
	ActionPerforme action{ this };
	Competence* cp{ this->getCompetence(Utilitaire::getRandomInteger(this->nbCompetence-1)) };
	if (cp->getCoutPm() > this->getPm()) {
		// en 0 se trouve l'attaque de base
		cp = this->getCompetence(0);
	}
	action.action = cp;

	//pansement
	action.cibles = action.action->getCiblage() == Ciblage::Self ? std::vector<Entite*>{ this } : std::vector<Entite*>{ &joueur };
	return action;
}