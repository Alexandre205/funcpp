#pragma once
#include<iostream>
#include<vector>

#include"Entite.h"
#include"Fight.h"
#include"Donjon.h"
namespace Obtention {
	ActionPerforme getActionPerforme(Perso& joueur, std::vector<Entite*>& ennemis);
	int getCibleIndice(std::vector<Entite*>& cibles);
	Direction getDirection(Salle* salle);
	int getValidInt(int lowerValue, int upperValue, std::string textInvalid);
}