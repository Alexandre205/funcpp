#pragma once
#include<string>

#include<array>
#include"erreurHandler.h"
#include"Competence.h"
class Entite
{
public:
	static const int NB_COMP_MAX = 4;
	static const int STAT_MAX_EFFECTIVE = 999;
	static const int STAT_MAX = 2500; // peut provoquer des bugs si atteint
protected:
	int pv, pvMax;
	int pm, pmMax;
	int attaque, defence, vitesse;
	int nbCompetence;
	std::array<Competence,NB_COMP_MAX> competences;
private:
	bool estInitialise;
	std::string nom;

	//int level, int exp
	//class
	//statut

	void modifierStat(int& stat, int modifSubi, int statMax);
public:

	std::string toString();

	Entite();
	Entite(const Entite& entite);
	Entite(std::string nom,int pv,int pvMax,int pm,int pmMax,int attaque,int defence,int vitesse);
	Entite(std::string nom, int pv, int pm, int attaque, int defence, int vitesse);

	
	void altererPv(int modifSubi);
	void altererPm(int modifSubi);
	void altererPvMax(int modifSubi);
	void altererPmMax(int modifSubi);
	void altererAttaque(int modifSubi);
	void altererDefence(int modifSubi);
	void altererVitesse(int modifSubi);

	void apprendreCompetence(Competence *newComp);
	void utiliserCompetence(int indiceDeCompetence, Entite& cible);

	virtual void attaqueDeBase(Entite& cible) = 0;

	//getteur
	bool estVivant();
	bool estInitialis();
	std::string getNom();

	virtual int getPv();
	virtual int getPvMax();
	virtual int getPm();
	virtual int getPmMax();
	virtual int getAttaque();
	virtual int getDefence();
	virtual int getVitesse();
};