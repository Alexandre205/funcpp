#pragma once
#include<vector>

#include"Monstre.h"
#include"Consommable.h"
#include"Casque.h"
#include"Arme.h"
#include"Armure.h"
#include"Botte.h"

struct DataEquipment {
	std::vector<Casque*> casques;
	std::vector<Arme*> armes;
	std::vector<Armure*> armures;
	std::vector<Botte*> bottes;
};

namespace FileManagement {
	namespace {
		const char* NOM_FILE_MONSTRE = "../ressources/Monstres.txt";
		const char* NOM_FILE_CONSUMABLE = "../ressources/Consumable.txt";
		const char* NOM_FILE_EQUIPEMENT = "../ressources/Equipment.txt";
	}
	
	std::vector<Monstre*> getMonstersFromFile();
	std::vector<Consommable*> getConsumablesFromFile();
	DataEquipment getEquipmentFromFile();
}