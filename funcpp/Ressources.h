#pragma once
#include<vector>
#include"FileManagement.h"
namespace Ressources {
	void initRessources();
	static DataEquipment dataEquipment;
	static std::vector<Monstre*> dataMonsters;
	static std::vector<Consommable*> dataConsommable;
}