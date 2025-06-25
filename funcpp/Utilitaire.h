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
		static std::mt19937 randomNumberGenerator;
		static std::mt19937 seedNumberGenerator;
		const char* NOM_FICHIER_LOG = "../ressources/log.txt";
		static int seed;
	}
	int applicationFormuleDeDegat(std::string formuleThéorique,Entite& attaquant,Entite& defenseur);
	int getRandomInteger(int lowestValue,int higestValue);
	int getRandomInteger(int higestValue);
	int getRandomInteger();

	void initSeed();
	void initSeed(int seed);
	int getGeneratedInteger(int lowestValue, int highterValue);
	int getGeneratedInteger(int highterValue);
	int getGeneratedInteger();

	//Replace '_' by ' ' and up the first caractere
	void polishMot(std::string& mot);

	//If test is false exit the app
	void testHandler(bool test, const char* message);

	//Exit the app
	void unexpectedExit(std::string message);
	void writeInLog(const char* message);
	void nettoyerLog();
};