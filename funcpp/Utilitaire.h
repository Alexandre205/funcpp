#pragma once
#include<string>
#include<random>

#include"Entite.h"
#include"AffichageConsole.h"
namespace Utilitaire
{
	

	//rend privée les variables
	namespace {
		static bool randomGeneratorActivate = false;
		static std::mt19937 numberGenerator;
		const char* NOM_FICHIER_LOG = "../ressources/log.txt";
	}
	int applicationFormuleDeDegat(std::string formuleThéorique,Entite& attaquant,Entite& defenseur);
	int getRandomInteger(int lowestValue,int higestValue);
	int getRandomInteger(int higestValue);
	int getRandomInteger();
	void polishMot(std::string& mot);
	void testHandler(bool test, const char* message, bool afficheSucces);
	void writeInLog(const char* message);
	void nettoyerLog();
};