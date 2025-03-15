#pragma once
#include<array>
#include<vector>
#include<deque>
#include"Monstre.h"
#include"Perso.h"

struct ActionPerforme {
	std::vector<Entite*> cibles;
	IUsable* action;
};
class Fight 
{
public:
	const static int NB_MONSTRE_MAX = 3;
private:
	int nbMonstre;
	std::vector<Monstre*> ennemis;
	Perso* joueur;
public:
	std::string toSring();

	Fight(Perso* joueur,std::vector<Monstre*> ennemis);
	//Fight(Perso* joueur, Monstre ennemis);
	void AddEnnemis(Monstre *ennemis);
	std::string listeMonstrePresent();
	void lancerCombat();
	bool isFinished();
	void majOrdreDAction(std::deque<Entite*>& ordreDAction);
};