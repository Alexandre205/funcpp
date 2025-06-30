#pragma once
#include<vector>

#include"Monstre.h"
#include"Consommable.h"

namespace FileManagement {
	namespace {
		const char* NOM_FILE_MONSTRE = "../ressources/Monstres.txt";
		const char* NOM_FILE_CONSUMABLE = "../ressources/Consumable.txt";
		const char* NOM_FILE_EQUIPEMENT = "../ressources/Equipment.txt";
	}
	
	std::vector<Monstre*> getMonstersFromFile();
	std::vector<Consommable*> getConsumablesFromFile();
	//std::vector<Equipement*> getEquipmentFromFile();
}