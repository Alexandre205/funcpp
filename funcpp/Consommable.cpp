#include "Consommable.h"

std::string Consommable::toString() {
	return Item::toString() + "\n";
}

Consommable::Consommable(std::string nom,std::string description) : Item(nom,description){}
Consommable::Consommable() : Consommable("vide","") {}