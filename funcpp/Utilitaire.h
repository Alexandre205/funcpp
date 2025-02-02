#pragma once
#include<string>

#include"Entite.h"
namespace Utilitaire
{
	static const char* NOM_FICHIER = "log.txt";
	int applicationFormuleDeDegat(std::string formuleThéorique,Entite& attaquant,Entite& defenseur);
	void testHandler(bool test, const char* message, bool afficheSucces);
	void writeInLog(const char* message);
	void nettoyerLog();
};