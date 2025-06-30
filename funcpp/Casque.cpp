#include "Casque.h"

std::string Casque::toString() {
	return Equipment::toString() + " (" + std::to_string(pvBonus) + " pv, " + std::to_string(pmBonus) + "pm)\n";
}

Casque::Casque(std::string nom, std::string description, int pvBonus, int pmBonus) : 
	Equipment(nom,description),pvBonus{pvBonus},pmBonus{pmBonus}{ }

int Casque::getPvBonus() {
	return pvBonus;
}
int Casque::getPmBonus() {
	return pmBonus;
}