#include "Botte.h"

std::string Botte::toString() {
	return Equipment::toString() + " (" + std::to_string(vitesseBonus) + " vit)\n";
}

Botte::Botte(std::string nom, std::string description, int vitesseBonus) : 
	Equipment(nom,description),vitesseBonus{vitesseBonus}{ }

int Botte::getVitesseBonus() {
	return vitesseBonus;
}