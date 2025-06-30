#include "Equipment.h"

std::string Equipment::toString() {
	return nom + " \"" + description + "\"\n";
}

Equipment::Equipment(std::string nom, std::string description) :nom{ nom }, description{ description } {}

std::string Equipment::getDescription() { return description; }
std::string Equipment::getNom() { return nom; }