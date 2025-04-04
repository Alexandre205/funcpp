#pragma once
#include<string>
#include<random>

#include"Entite.h"
#include"AffichageConsole.h"
namespace Utilitaire
{
	static const char* NOM_FICHIER = "log.txt";
	static bool randomGeneratorActivate = false;
	static std::mt19937 numberGenerator;
	int applicationFormuleDeDegat(std::string formuleThéorique,Entite& attaquant,Entite& defenseur);
	int getRandomInteger(int lowestValue,int higestValue);
	int getRandomInteger(int higestValue);
	int getRandomInteger();
	void testHandler(bool test, const char* message, bool afficheSucces);
	void writeInLog(const char* message);
	void nettoyerLog();
};