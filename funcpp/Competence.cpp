#include "Competence.h"
#include "Entite.h"

Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet, competence.coutPm,competence.multiCible){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, int coutPm, bool multiCible) :
	nom{ nom }, description{ description }, effet{ effet }, coutPm{ coutPm }, multiCible{ multiCible }, possesseur{NULL} 
{};

void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	possesseur = nouvPossesseur;
}

void Competence::utiliser(Entite& cible) {
	effet(cible, 10);
}
void Competence::utiliser(std::vector<Entite*> cibles) {
	for (Entite *cible : cibles) {
		utiliser(*cible);
	}
}