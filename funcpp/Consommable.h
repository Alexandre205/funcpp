#pragma once
#include"Item.h"
#include"Entite.h"
class Consommable : public Item 
{
private:
	//effets
public:
	Consommable();
	Consommable(std::string nom,std::string description);
	virtual void utilisation(Entite& cible) = 0;
};