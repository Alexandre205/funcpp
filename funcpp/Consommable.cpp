#include "Consommable.h"
#include "Utilitaire.h"


std::string Consommable::toString() {
	return Item::toString() + "\n";
}

Consommable::Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet, std::string formule, Entite* possesseur) :
	Item(nom,description){
	IUsable::effet = effet;
	IUsable::formule = formule;
	IUsable::possesseur = possesseur;
}

void Consommable::utiliser(Entite& cible) {
	int valeur = Utilitaire::applicationFormuleDeDegat(formule, *possesseur, cible);
	effet(cible, valeur);
}