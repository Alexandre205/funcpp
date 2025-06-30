#include "Competence.h"
#include "Entite.h"
#include "Utilitaire.h"

std::string Competence::toString() {
	return "- " + nom + " " + std::to_string(coutPm) + " pm.";
}

Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet,competence.formule,competence.ciblage, competence.coutPm,competence.priorite){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDegat,ICiblage* ciblage, int coutPm,int priorite) :
	nom{ nom }, description{ description }, coutPm {coutPm}{
	IUsable::effet = effet;
	IUsable::formule = formuleDegat;
	IUsable::possesseur = possesseur;
	IUsable::ciblage = ciblage;
	IUsable::priorite = priorite;
};
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDeDegat, ICiblage* ciblage, int coutPm) :
	Competence(nom, description, effet, formuleDeDegat, ciblage, coutPm, 0) {
};
Competence::Competence(std::string nom, std::string description, int iEffet, std::string formuleDeDegat, int iICiblage, int coutPm, int priorite) :
	Competence(nom, description, Effets::intToEffet(iEffet), formuleDeDegat, ICiblage::intToICiblage(iICiblage), coutPm, priorite) {
};

int Competence::getCoutPm() {
	return coutPm;
}
int Competence::getPriority() {
	return priorite;
}
std::string Competence::getNom() {
	return  nom;
}

void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	Utilitaire::testHandler(nouvPossesseur != NULL,"Possesseur de competence null");
	possesseur = nouvPossesseur;
}

void Competence::utiliser(std::vector<Entite*> cibles) {
	Affichage::afficher(possesseur->getNom() + " utilise " + nom + ", -");
	possesseur->altererPm(-coutPm);
	for (Entite* cible : cibles) {
		int valeurAjoute = Utilitaire::applicationFormuleDeDegat(this->formule,*possesseur,*cible);
		this->effet(*cible, valeurAjoute);
	}
}

std::vector<Entite*> Competence::getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) {
	return ciblage->selectionnerCible(ennemis,allie);
}