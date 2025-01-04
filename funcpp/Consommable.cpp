#include "Consommable.h"

Consommable::Consommable(std::string nom,std::string description) : Item(nom,description){}
Consommable::Consommable() : Consommable("vide","") {}