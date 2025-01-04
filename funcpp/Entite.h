#pragma once
#include<string>
#include"erreurHandler.h"
class Entite
{
protected:
	int pv, pvMax;
	int pm, pmMax;
	int attaque, defence, vitesse;
private:
	bool estInitialise;
	std::string nom;

	//int level
	//class

	void modifierStat(int& stat, int modifSubi, int statMax);
public:
	static const int STAT_MAX_EFFECTIVE = 999;
	static const int STAT_MAX = 2500; // peut provoquer des bugs si atteint

	std::string toString();

	Entite();
	Entite(const Entite& entite);
	Entite(std::string nom,int pv,int pvMax,int pm,int pmMax,int attaque,int defence,int vitesse);
	Entite(std::string nom, int pv, int pm, int attaque, int defence, int vitesse);

	std::string getNom();
	
	void altererPv(int modifSubi);
	void altererPm(int modifSubi);
	void altererPvMax(int modifSubi);
	void altererPmMax(int modifSubi);
	void altererAttaque(int modifSubi);
	void altererDefence(int modifSubi);
	void altererVitesse(int modifSubi);


	virtual void attaqueDeBase(Entite& cible) = 0;

	//getteur
	bool estVivant();
	bool estInitialis();

	virtual int getPv();
	virtual int getPvMax();
	virtual int getPm();
	virtual int getPmMax();
	virtual int getAttaque();
	virtual int getDefence();
	virtual int getVitesse();
};