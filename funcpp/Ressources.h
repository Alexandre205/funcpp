#pragma once
#include<vector>
#include"FileManagement.h"

namespace Ressources {
	void initRessources();
	extern DataEquipment dataEquipment;
	extern std::vector<Monstre*> dataMonsters;
	extern std::vector<Consommable*> dataConsommable;
}