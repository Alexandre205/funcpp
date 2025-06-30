#pragma once
#include<vector>

#include"Monstre.h"
#include"Consommable.h"

namespace FileManagement {
	namespace {
		const char* NOM_FILE_MONSTRE = "../ressources/Monstres.txt";
		const char* NOM_FILE_CONSUMABLE = "../ressources/Consumable.txt";
	}
	
	std::vector<Monstre*> getMonstersFromFile();
	std::vector<Consommable*> getConsumablesFromFile();
}