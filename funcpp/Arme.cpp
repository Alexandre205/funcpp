#include "Arme.h"

std::string Arme::toString() {
	return Equipment::toString() + " (" + std::to_string(attaqueBonus) + " atk)\n";
}

Arme::Arme(std::string nom,std::string description,int attaqueBonus) :
	Equipment(nom,description), attaqueBonus{attaqueBonus} { }

int Arme::getAttaqueBonus() {
	return attaqueBonus;
}