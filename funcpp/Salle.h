#pragma once
#include<array>
#include"Monstre.h"
class Salle 
{
public:
	const static int NB_MONSTRE_MAX = 3;
private:
	int numero;
	int nbMonstre;
	std::array<Monstre, NB_MONSTRE_MAX> ennemis;
public:
	Salle(int numero, Monstre ennemis[NB_MONSTRE_MAX]);
	void AddEnnemis(Monstre ennemis);
	std::string listeMonstrePresent();
	std::string toSring();
};