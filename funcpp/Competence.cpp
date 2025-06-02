#include "Competence.h"
#include "Entite.h"
#include "Utilitaire.h"

std::string Competence::toString() {
	return "- " + nom + " " + std::to_string(coutPm) + " pm.";
}

Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet,competence.formule,competence.ciblage, competence.coutPm){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDegat,ICiblage* ciblage, int coutPm) :
	nom{ nom }, description{ description }, coutPm {coutPm}{
	IUsable::effet = effet;
	IUsable::formule = formuleDegat;
	IUsable::possesseur = possesseur;
	IUsable::ciblage = ciblage;
};

int Competence::getCoutPm() {
	return coutPm;
}

void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	Utilitaire::testHandler(nouvPossesseur != NULL,"Possesseur de competence null",false);
	possesseur = nouvPossesseur;
}

void Competence::utiliser(std::vector<Entite*> cibles) {
	Affichage::afficher(possesseur->getNom() + " utilise " + nom + ", -");
	possesseur->altererPm(-coutPm);
	ciblage->appliquerEffet(effet, cibles, *possesseur, formule);
}
std::vector<Entite*> Competence::getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) {
	return ciblage->selectionnerCible(ennemis,allie);
}