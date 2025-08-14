#include "Monstre.h"
#include "Fight.h"
#include"Utilitaire.h"

std::string Monstre::toString() {
	return getNom() + " (" + std::to_string(getPv()) + "/" + std::to_string(getPvMax()) + "pv)";
}



Monstre::Monstre(const Monstre& monstre) : Monstre(monstre.nom,monstre.stats, monstre.goldRecompense) {
	for (int i{ 0 }; i < monstre.nbCompetence;i++) {
		this->apprendreCompetence(new Competence(monstre.competences[i]));
	}
}

Monstre::Monstre(std::string nom, std::array<int, NB_STAT> stats, int goldRecompense) : Entite{ nom,stats }, goldRecompense{ goldRecompense } {};


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