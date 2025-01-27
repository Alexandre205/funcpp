#include "Competence.h"


Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet, competence.coutPm){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, int coutPm) :
	nom{ nom }, description{ description }, effet{ effet }, coutPm{ coutPm }, possesseur{NULL} {
};


void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	possesseur = nouvPossesseur;
}

void Competence::utiliser(Entite& cible) {
	effet(cible, 10);
}