#pragma once
#include<iostream>
#include<vector>

#include"Entite.h"
#include"Fight.h"
namespace Obtention {
	ActionPerforme getActionPerforme(Entite& joueur, std::vector<Monstre*>& ennemis);
}