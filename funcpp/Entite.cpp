#include "Entite.h"
#include"Utilitaire.h"
std::string Entite::toString() {
	using namespace std;
	return nom + " (" + to_string(pv) + "/" + to_string(getPvMax()) + "pv)(" + to_string(pm) + "/" + to_string(getPmMax()) + "pm)("+to_string(getAttaque())+" "+to_string(getDefence())+" "+to_string(getVitesse())+")";
}

Entite::Entite() :estInitialise{ false } {};
Entite::Entite(const Entite& entite):
	Entite(entite.nom,entite.pv,entite.pvMax,entite.pm,entite.pmMax,entite.attaque,entite.defence,entite.vitesse){ }
Entite::Entite(std::string nom, int pv, int pvMax, int pm, int pmMax, int attaque, int defence, int vitesse):
	nom{ nom }, pv{ 0 }, pvMax{ 0 }, pm{ 0 }, pmMax{ 0 }, attaque{ 0 }, defence{ 0 }, vitesse{ 0 }, nbCompetence{0}, estInitialise{ true } {
	altererPvMax(pvMax);
	altererPv(pv);
	altererPmMax(pmMax);
	altererPm(pm);
	altererAttaque(attaque);
	altererDefence(defence);
	altererVitesse(vitesse);
}
Entite::Entite(std::string nom, int pv, int pm,int attaque, int defence, int vitesse):
	Entite(nom, pv, pv, pm, pm,attaque,defence,vitesse){}

void Entite::modifierStat(int& stat, int modifSubi, int statMax) {
	stat += modifSubi;
	if (stat <= 0) {
		stat = 0;
	}
	if (stat >= statMax) {
		stat = statMax;
	}
}
void Entite::altererPv(int modifSubi) {
	modifierStat(pv, modifSubi, getPvMax());
}
void Entite::altererPm(int modifSubi) {
	modifierStat(pm, modifSubi, getPmMax());
}
void Entite::altererPvMax(int modifSubi) {
	modifierStat(pvMax, modifSubi, STAT_MAX);
	if (pv > getPvMax()) {
		pv = getPvMax();
	}
	Utilitaire::testHandler(pvMax != STAT_MAX, "check limite pvMax",false);
}
void Entite::altererPmMax(int modifSubi) {
	modifierStat(pmMax, modifSubi, STAT_MAX);
	if (pm > getPmMax()) {
		pm = getPmMax();
	}
	Utilitaire::testHandler(pmMax != STAT_MAX, "check limite pmMax",false);
}
void Entite::altererAttaque(int modifSubi) {
	modifierStat(attaque, modifSubi, STAT_MAX);
	Utilitaire::testHandler(attaque != STAT_MAX, "check limite attaque",false);
}
void Entite::altererDefence(int modifSubi) {
	modifierStat(defence, modifSubi, STAT_MAX);
	Utilitaire::testHandler(defence != STAT_MAX, "check limite defence",false);
}
void Entite::altererVitesse(int modifSubi) {
	modifierStat(vitesse, modifSubi, STAT_MAX);
	Utilitaire::testHandler(vitesse != STAT_MAX, "check limite vitesse",false);
}

void Entite::apprendreCompetence(Competence *newComp) {
	if (nbCompetence < NB_COMP_MAX) {
		newComp->ajouterPossesseur(this);
		competences[nbCompetence] = *newComp;
		nbCompetence++;
	}
	else {
		Utilitaire::writeInLog("Deja trops de competence");
	}
}

void Entite::utiliserCompetence(int indiceDeCompetence, std::vector<Entite*> cibles) {
	Utilitaire::testHandler(indiceDeCompetence < nbCompetence && indiceDeCompetence >= 0, "indice de la competence hors portée", false);
	competences[indiceDeCompetence].utiliser(cibles);
}
std::string Entite::getNom() { return nom; }
bool Entite::estInitialis() { return estInitialise; }
bool Entite::estVivant() {return pv > 0;}

int Entite::getPv() {
	return pv;
}
int Entite::getPvMax() {
	return pvMax <= STAT_MAX_EFFECTIVE ? pvMax : STAT_MAX_EFFECTIVE;
}
int Entite::getPm() {
	return pm;
}
int Entite::getPmMax() {
	return pmMax <= STAT_MAX_EFFECTIVE ? pmMax : STAT_MAX_EFFECTIVE;
}
int Entite::getAttaque() {
	return attaque<= STAT_MAX_EFFECTIVE ? attaque:STAT_MAX_EFFECTIVE;
}
int Entite::getDefence() {
	return defence <= STAT_MAX_EFFECTIVE ? defence : STAT_MAX_EFFECTIVE;
}
int Entite::getVitesse() {
	return vitesse <= STAT_MAX_EFFECTIVE ? vitesse : STAT_MAX_EFFECTIVE;
}