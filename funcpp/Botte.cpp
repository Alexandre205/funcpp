#include "Botte.h"

Botte::Botte(std::string nom, std::string description, int vitesseBonus) : 
	Item(nom,description),vitesseBonus{vitesseBonus}{ }

int Botte::getVitesseBonus() {
	return vitesseBonus;
}