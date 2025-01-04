#include "Arme.h"


Arme::Arme(std::string nom,std::string description,int attaqueBonus) :Item(nom,description), attaqueBonus{attaqueBonus} {

}

int Arme::getAttaqueBonus() {
	return attaqueBonus;
}