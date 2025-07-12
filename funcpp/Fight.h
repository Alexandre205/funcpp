#pragma once
#include<array>
#include<vector>
#include<deque>
#include"Monstre.h"
#include"Perso.h"

struct ActionPerforme {
	Entite* lanceur;
	std::vector<Entite*> cibles;
	IUsable* action;
};
class Fight 
{
public:
	const static int NB_MONSTRE_MAX = 3;
private:
	std::vector<Monstre>& ennemis;
	Perso* joueur;
public:
	std::string toSring();

	Fight(Perso* joueur,std::vector<Monstre>& ennemis);
	void addEnnemis(Monstre ennemis);
	std::string listeMonstrePresent();
	void lancerCombat();

	//private
	bool isFinished();
	void majOrdreDAction(std::deque<Entite*>& ordreDAction);
};