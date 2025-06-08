#include "Consommable.h"
#include "Utilitaire.h"


std::string Consommable::toString() {
	return Item::toString() + "\n";
}

Consommable::Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet, std::string formule, Entite* possesseur,int priorite) :
	Item(nom,description){
	IUsable::effet = effet;
	IUsable::formule = formule;
	IUsable::possesseur = possesseur;
	IUsable::priorite = priorite;
}
Consommable::Consommable(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formule, Entite* possesseur) :
	Consommable{ nom,description,effet,formule,possesseur,0 } {};

void Consommable::utiliser(std::vector<Entite*> cibles) {
	for (Entite* cible : cibles) {
		int valeur = Utilitaire::applicationFormuleDeDegat(formule, *possesseur, *cible);
		effet(*cible, valeur);
	}
}
int Consommable::getPriority() {
	return priorite;
}