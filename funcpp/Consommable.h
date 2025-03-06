#pragma once
#include"Item.h"
#include"Entite.h"
#include"IUsable.h"
#include"Effets.h"
class Consommable : public Item, public IUsable
{
public:

	std::string toString();

	Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet,std::string formule,Entite* possesseur);
	void utiliser(Entite& cible);
};