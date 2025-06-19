#pragma once
#include<iostream>
#include<vector>

#include"Entite.h"
#include"Fight.h"
#include"Donjon.h"
namespace Obtention {
	ActionPerforme getActionPerforme(Entite& joueur, std::vector<Monstre*>& ennemis);
	int getCibleIndice(std::vector<Entite*>& cibles);
	Direction getDirection(Salle* salle);
}