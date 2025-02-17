#include "Armure.h"

std::string Armure::toString() {
	return Item::toString() + " (" + std::to_string(defenceBonus) + " def)\n";
}

Armure::Armure(std::string nom, std::string description, int defenceBonus) :
	Item(nom, description), defenceBonus{ defenceBonus } {};

int Armure::getDefenceBonus() {
	return defenceBonus;
}