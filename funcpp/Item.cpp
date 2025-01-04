#include "Item.h"

std::string Item::toString() {
	return nom + " : " + description +"\n";
}

Item::Item(std::string nom, std::string description) :nom{ nom }, description{ description } {}

std::string Item::getDescription() {
	return description;
}
std::string Item::getNom() {
	return nom;
}