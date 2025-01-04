#pragma once
#include<string>
#include"Item.h"
class Arme:public Item
{
private:
	int attaqueBonus;
	//ElementD'attaque
	//Competence lié
public:
	Arme(std::string nom,std::string description,int attaqueBonus);
	int getAttaqueBonus();
};