#pragma once
#include<vector>
#include<map>
#include"FileManagement.h"

namespace Ressources {
	void initRessources();
	extern DataEquipment dataEquipment;
	extern std::vector<Monstre> dataMonsters;
	extern std::vector<Consommable> dataConsommable;
	extern std::map<int, std::vector<Competence>> dataPlayerComp;
}