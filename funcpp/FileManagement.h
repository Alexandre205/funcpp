#pragma once
#include<vector>

#include"Monstre.h"

namespace FileManagement {
	namespace {
		const char* NOM_FILE_MONSTRE = "../ressources/Monstres.txt";
	}
	
	std::vector<Monstre*> getMonstersFromFile();
}