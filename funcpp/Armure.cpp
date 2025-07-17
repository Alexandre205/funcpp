#include "Armure.h"

std::string Armure::toString() {
	return Equipment::toString() + " (" + std::to_string(defenceBonus) + " def)\n";
}

Armure::Armure(std::string nom, std::string description, int defenceBonus, int defenceMagiqueBonus) :
	Equipment(nom, description), defenceBonus{ defenceBonus }, defenceMagiqueBonus{defenceMagiqueBonus} {
};

int Armure::getDefenceBonus() {
	return defenceBonus;
}
int Armure::getDefenceMagiqueBonus() {
	return defenceMagiqueBonus;
}