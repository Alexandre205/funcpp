#include "Competence.h"
#include "Entite.h"
#include "Utilitaire.h"

std::string Competence::toString() {
	return "- " + nom + " (" + description + ") " + std::to_string(coutPm) + " pm.";
}

Competence::Competence() {};
Competence::Competence(const Competence& competence) :
	Competence(competence.nom, competence.description, competence.effet,competence.formuleDeDegat, competence.coutPm,competence.multiCible){}
Competence::Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet,std::string formuleDeDegat, int coutPm, bool multiCible) :
	nom{ nom }, description{ description }, effet{ effet }, formuleDeDegat{ formuleDeDegat }, coutPm {
	coutPm
}, multiCible{ multiCible }, possesseur{ NULL }
{};

void Competence::ajouterPossesseur(Entite *nouvPossesseur) {
	Utilitaire::testHandler(nouvPossesseur != NULL,"Possesseur de competence null",false);
	possesseur = nouvPossesseur;
}

void Competence::utiliser(Entite& cible) {
	int n = Utilitaire::applicationFormuleDeDegat(formuleDeDegat, *possesseur, cible);
	effet(cible, n);
}
void Competence::utiliser(std::vector<Entite*> cibles) {
	if (possesseur->getPm() >= coutPm) {
		Affichage::afficher(possesseur->getNom() + " utilise " + nom+", -");
		possesseur->altererPm(-coutPm);
		for (Entite* cible : cibles) {
			utiliser(*cible);
		}
	}
	else {
		Affichage::afficher("Pas assez de PM pour lancer " + nom + "\n");
		//retourner à la selection de competence
	}
}