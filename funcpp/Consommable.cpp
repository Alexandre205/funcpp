#include "Consommable.h"
#include "Utilitaire.h"
#include"AffichageConsole.h"


std::string Consommable::toString() {
	return nom + " \"" + description + "\"\n";
}

Consommable::Consommable(std::string nom,std::string description,int price, std::function<void(Entite&, int)> effet, std::string formule, Ciblage ciblage,int priorite) :
	nom{ nom }, description{ description } {
	ILootable::price = price;
	IUsable::effet = effet;
	IUsable::formule = formule;
	IUsable::priorite = priorite;
	IUsable::ciblage = ciblage;
}
Consommable::Consommable(std::string nom, std::string description,int price, std::function<void(Entite&, int)> effet, std::string formule, Ciblage ciblage) :
	Consommable{ nom,description,price,effet,formule,ciblage,0 } {};

Consommable::Consommable(std::string nom, std::string description,int price, int iEffect, std::string formule, int iCiblage, int priority) :
	Consommable{ nom,description,price,Effets::intToEffet(iEffect),formule,ICiblage::intToICiblage(iCiblage),priority } {};
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
std::vector<Entite*> Consommable::getCibles(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie) {
	return infoCiblage[ciblage].ciblage->selectionnerCible(ennemis, allie);
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
Ciblage Consommable::getCiblage() {
	return ciblage;
}
int Consommable::getPrice() {
	return price;
}