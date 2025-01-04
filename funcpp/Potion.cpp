#include "Potion.h"

Potion::Potion(std::string nom, std::string description, std::function<void(Entite&, int)> effet, int puissance) : 
	Consommable(nom, description), puissance{ puissance }, effet{effet} {}

void Potion::utilisation(Entite& cible) {
	effet(cible, puissance);
}