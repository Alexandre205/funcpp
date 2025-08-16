#pragma once
#include<string>
#include<array>
#include"Competence.h"
class Perso;
class Monstre;
struct ActionPerforme;
enum Stats {
	PV_MAX,PM_MAX,ATK_P,ATK_M,DEF_P,DEF_M,VIT
};
class Entite
{
public:
	static const int NB_COMP_MAX = 4;
	static const int STAT_MAX_EFFECTIVE = 999;
	static const int STAT_MAX = 2500; // peut provoquer des bugs si atteint
	static const int NB_STAT = 7;
	static const std::array<std::string, NB_STAT> statToString;
protected:
	std::array<int, NB_STAT> stats;
	std::string nom;
	int pv, pm;
	int nbCompetence;
	int level;
	std::array<Competence,NB_COMP_MAX> competences;
private:
	

	//class
	//statut

	static void modifierStat(int& stat, int modifSubi, int statMax);
public:

	std::string toString();

	Entite();
	//Entite(const Entite& entite);
	Entite(std::string nom, std::array<int, NB_STAT> stats,int level);
	Entite(std::string nom, std::array<int, NB_STAT> stats);
	//Entite(std::string nom,int pv,int pvMax,int pm,int pmMax, int attaque, int attaqueMagique, int defence, int defenceMagique, int vitesse);
	//Entite(std::string nom, int pv, int pm, int attaque, int attaqueMagique, int defence, int defenceMagique, int vitesse);

	static bool comparerVitesse(Entite* e1, Entite* e2);
	
	void altererPv(int modifSubi);
	void altererPm(int modifSubi);
	void altererPvMax(int modifSubi);
	void altererPmMax(int modifSubi);
	void altererAttaque(int modifSubi);
	void altererAttaqueMagique(int modifier);
	void altererDefence(int modifSubi);
	void altererDefenceMagique(int modifSubi);
	void altererVitesse(int modifSubi);

	void apprendreCompetence(Competence *newComp);



	//getteur
	bool estVivant();
	std::string getNom();
	virtual int getPv();
	virtual int getPvMax();
	virtual int getPm();
	virtual int getPmMax();
	virtual int getAttaque();
	virtual int getAttaqueMagique();
	virtual int getDefence();
	virtual int getDefenceMagique();
	virtual int getVitesse();
	std::array<int, NB_STAT>* getStats();
	
	int getNbCompetence();
	Competence* getCompetence(int indice);
	virtual ActionPerforme getAction(Perso& joueur,std::vector<Monstre>& monstres) = 0;
	std::string getListCompetence();
};