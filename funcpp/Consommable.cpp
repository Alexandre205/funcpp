#include "Consommable.h"
#include "Utilitaire.h"
#include"AffichageConsole.h"


std::string Consommable::toString() {
	return nom + " \"" + description + "\"\n";
}

Consommable::Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet, std::string formule,ICiblage* ciblage,int priorite) :
	nom{ nom }, description{ description } {
	IUsable::effet = effet;
	IUsable::formule = formule;
	IUsable::priorite = priorite;
	IUsable::ciblage = ciblage;
}
Consommable::Consommable(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formule, ICiblage* ciblage) :
	Consommable{ nom,description,effet,formule,ciblage,0 } {};

Consommable::Consommable(std::string nom, std::string description, int iEffect, std::string formule, int iCiblage, int priority) :
	Consommable{ nom,description,Effets::intToEffet(iEffect),formule,ICiblage::intToICiblage(iCiblage),priority } {};
void Consommable::ajouterPossesseur(Entite* nouvPossesseur) {
	Utilitaire::testHandler(nouvPossesseur != NULL, "Possesseur de competence null");
	possesseur = nouvPossesseur;
}
void Consommable::utiliser(std::vector<Entite*> cibles) {
	Affichage::afficher(possesseur->getNom()+" utilise l'objet "+nom+"\n");
	for (Entite* cible : cibles) {
		int valeur = Utilitaire::applicationFormuleDeDegat(formule, *possesseur, *cible);
		effet(*cible, valeur);
	}
}
std::vector<Entite*> Consommable::getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) {
	return ciblage->selectionnerCible(ennemis, allie);
}
int Consommable::getPriority() {
	return priorite;
}
std::string Consommable::getNom() {
	return nom;
}
std::string Consommable::getDescription() {
	return  description;
}