#include "Botte.h"

std::string Botte::toString() {
	return Item::toString() + " (" + std::to_string(vitesseBonus) + " vit)\n";
}

Botte::Botte(std::string nom, std::string description, int vitesseBonus) : 
	Item(nom,description),vitesseBonus{vitesseBonus}{ }

int Botte::getVitesseBonus() {
	return vitesseBonus;
}