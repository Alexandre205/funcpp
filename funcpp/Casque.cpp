#include "Casque.h"

Casque::Casque(std::string nom, std::string description, int pvBonus, int pmBonus) : 
	Item(nom,description),pvBonus{pvBonus},pmBonus{pmBonus}{ }

int Casque::getPvBonus() {
	return pvBonus;
}
int Casque::getPmBonus() {
	return pmBonus;
}