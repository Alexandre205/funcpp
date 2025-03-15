#include "Competence.h"
#include "Entite.h"
#include "Utilitaire.h"

std::string Competence::toString() {
	return "- " + nom + " (" + description + ") " + std::to_string(coutPm) + " pm.";
}

Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet,competence.formule, competence.coutPm){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDegat, int coutPm) :
	nom{ nom }, description{ description }, coutPm {coutPm}{
	IUsable::effet = effet;
	IUsable::formule = formuleDegat;
	IUsable::possesseur = possesseur;
};

void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	Utilitaire::testHandler(nouvPossesseur != NULL,"Possesseur de competence null",false);
	possesseur = nouvPossesseur;
}

void Competence::utiliser(std::vector<Entite*> cibles) {
	Affichage::afficher(possesseur->getNom() + " utilise " + nom + ", -");
	possesseur->altererPm(-coutPm);
	for (Entite* cible : cibles) {
		int valeur = Utilitaire::applicationFormuleDeDegat(formule, *possesseur, *cible);
		effet(*cible, valeur);
	}
}