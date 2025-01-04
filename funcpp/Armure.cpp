#include "Armure.h"

Armure::Armure(std::string nom, std::string description, int defenceBonus) :
	Item(nom, description), defenceBonus{ defenceBonus } {};

int Armure::getDefenceBonus() {
	return defenceBonus;
}