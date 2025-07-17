#pragma once

#include "Equipment.h"
class Arme:public Equipment
{
private:
	int attaqueBonus;
	int attaqueMagiqueBonus;
	//ElementD'attaque
	//Competence lié
public:

	std::string toString();

	Arme(std::string nom,std::string description,int attaqueBonus,int attaqueMagiqueBonus);
	int getAttaqueBonus();
	int getAttaqueMagiqueBonus();
};