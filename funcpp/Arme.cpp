#include "Arme.h"

std::string Arme::toString() {
	return Equipment::toString() + " (" + std::to_string(attaqueBonus) + " atk)\n";
}

Arme::Arme(std::string nom,std::string description,int attaqueBonus,int attaqueMagiqueBonus) :
	Equipment(nom, description), attaqueBonus{ attaqueBonus }, attaqueMagiqueBonus{attaqueMagiqueBonus} {
}

int Arme::getAttaqueBonus() {
	return attaqueBonus;
}
int Arme::getAttaqueMagiqueBonus() {
	return attaqueMagiqueBonus;
}