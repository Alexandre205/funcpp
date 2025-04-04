#include "Entite.h"
#include "Utilitaire.h"
std::string Entite::toString() {
	using namespace std;
	string output = nom + " (" + to_string(pv) + "/" + to_string(getPvMax()) + "pv)(" + to_string(pm) + "/" + to_string(getPmMax()) + "pm)(" + to_string(getAttaque()) + " atk, " + to_string(getDefence()) + " def, " + to_string(getVitesse()) + " vit)\n";
	int i = 0;
	for (i; i < nbCompetence; i++) {
		output += competences[i].toString() + "\n";
	}
	for (i; i < NB_COMP_MAX; i++) {
		output += "-\n";
	}
	return output;
}

Entite::Entite(){};
Entite::Entite(const Entite& entite):
	Entite(entite.nom,entite.pv,entite.pvMax,entite.pm,entite.pmMax,entite.attaque,entite.defence,entite.vitesse){ }
Entite::Entite(std::string nom, int pv, int pvMax, int pm, int pmMax, int attaque, int defence, int vitesse):
	nom{ nom }, pv{ pv }, pvMax{ pvMax }, pm{ pm }, pmMax{ pmMax }, attaque{ attaque }, defence{ defence }, vitesse{ vitesse }, nbCompetence{0} 
{
	// quelque modification de robustesse a prevoir
}
Entite::Entite(std::string nom, int pv, int pm,int attaque, int defence, int vitesse):
	Entite(nom, pv, pv, pm, pm,attaque,defence,vitesse){}

bool Entite::comparerVitesse(Entite* e1, Entite* e2) {
	return  e1->getVitesse()>e2->getVitesse();
}

void Entite::modifierStat(int& stat, int modifSubi, int statMax) {
	Affichage::afficher(std::to_string(abs(modifSubi)));
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
	Affichage::afficher("pv\n");
}
void Entite::altererPm(int modifSubi) {
	modifierStat(pm, modifSubi, getPmMax());
	Affichage::afficher("pm\n");
}
void Entite::altererPvMax(int modifSubi) {
	modifierStat(pvMax, modifSubi, STAT_MAX);
	if (pv > getPvMax()) {
		pv = getPvMax();
	}
	Affichage::afficher("pv max\n");
	Utilitaire::testHandler(pvMax != STAT_MAX, "check limite pvMax",false);
}
void Entite::altererPmMax(int modifSubi) {
	modifierStat(pmMax, modifSubi, STAT_MAX);
	if (pm > getPmMax()) {
		pm = getPmMax();
	}
	Affichage::afficher("pm max\n");
	Utilitaire::testHandler(pmMax != STAT_MAX, "check limite pmMax",false);
}
void Entite::altererAttaque(int modifSubi) {
	modifierStat(attaque, modifSubi, STAT_MAX);
	Affichage::afficher("atk\n");
	Utilitaire::testHandler(attaque != STAT_MAX, "check limite attaque",false);
}
void Entite::altererDefence(int modifSubi) {
	modifierStat(defence, modifSubi, STAT_MAX);
	Affichage::afficher("def\n");
	Utilitaire::testHandler(defence != STAT_MAX, "check limite defence",false);
}
void Entite::altererVitesse(int modifSubi) {
	modifierStat(vitesse, modifSubi, STAT_MAX);
	Affichage::afficher("vit\n");
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

std::string Entite::getNom() { return nom; }
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
int Entite::getNbCompetence() {
	return nbCompetence;
}
Competence* Entite::getCompetence(int indice) {
	Utilitaire::testHandler(indice < nbCompetence && indice >= 0, "indice de la competence hors portée", false);
	return &competences[indice];
}
std::string Entite::getListCompetence() {
	std::string liste="";
	for (int i = 0; i < nbCompetence; i++) {
		liste.append(std::to_string(i + 1) + this->getCompetence(i)->toString() + "\n");
	}

	return liste;
}