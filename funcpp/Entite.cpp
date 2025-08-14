#include "Entite.h"
#include "Utilitaire.h"

const std::array<std::string, Entite::NB_STAT> Entite::statToString = { "PvMax","PmMax","AtkP","AtkM","DefP","DefM","Vit" };
std::string Entite::toString() {
	using namespace std;
	string output = nom + " (" + to_string(getPv()) + "/" + to_string(getPvMax()) + "pv)(" + to_string(getPm()) + "/" + to_string(getPmMax()) + "pm)(" + to_string(getAttaque()) + " atk_p, " + to_string(getDefence()) + " def_p, " + to_string(getVitesse()) + " vit)\n";
	int i = 0;
	for (i; i < nbCompetence; i++) {
		output += competences[i].toString() + "\n";
	}
	for (i; i < NB_COMP_MAX; i++) {
		output += "-\n";
	}
	return output;
}

Entite::Entite(){};//pas utile je pense
Entite::Entite(std::string nom, std::array<int, NB_STAT> stats) :
	nom{ nom }, stats{ stats }, nbCompetence{ 0 }, pv{ stats[Stats::PV_MAX] }, pm{stats[Stats::PM_MAX]} {}

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
}
void Entite::altererPm(int modifSubi) {
	modifierStat(pm, modifSubi, getPmMax());
}
void Entite::altererPvMax(int modifSubi) {
	modifierStat(stats[Stats::PV_MAX], modifSubi, STAT_MAX);
	if (pv > getPvMax()) {
		pv = getPvMax();
	}
	Utilitaire::testHandler(stats[Stats::PV_MAX] != STAT_MAX, "check limite pvMax");
}
void Entite::altererPmMax(int modifSubi) {
	modifierStat(stats[Stats::PM_MAX], modifSubi, STAT_MAX);
	if (pm > getPmMax()) {
		pm = getPmMax();
	}
	Utilitaire::testHandler(stats[Stats::PM_MAX] != STAT_MAX, "check limite pmMax");
}
void Entite::altererAttaque(int modifSubi) {
	modifierStat(stats[Stats::ATK_P], modifSubi, STAT_MAX);
	Utilitaire::testHandler(stats[Stats::ATK_P] != STAT_MAX, "check limite attaque");
}
void Entite::altererAttaqueMagique(int modifSubi) {
	modifierStat(stats[Stats::ATK_M], modifSubi, STAT_MAX);
	Utilitaire::testHandler(stats[Stats::ATK_M] != STAT_MAX, "check limite atk_m");
}
void Entite::altererDefence(int modifSubi) {
	modifierStat(stats[Stats::DEF_P], modifSubi, STAT_MAX);
	Utilitaire::testHandler(stats[Stats::DEF_P] != STAT_MAX, "check limite defence");
}
void Entite::altererDefenceMagique(int modifSubi) {
	modifierStat(stats[Stats::DEF_M], modifSubi, STAT_MAX);
	Utilitaire::testHandler(stats[Stats::DEF_M] != STAT_MAX, "check limite def_m");
}
void Entite::altererVitesse(int modifSubi) {
	modifierStat(stats[Stats::VIT], modifSubi, STAT_MAX);
	Utilitaire::testHandler(stats[Stats::VIT] != STAT_MAX, "check limite vitesse");
}

void Entite::apprendreCompetence(Competence *newComp) {
	if (nbCompetence < NB_COMP_MAX) {
		competences[nbCompetence] = *newComp;
		competences[nbCompetence].ajouterPossesseur(this);
		nbCompetence++;
	}
	else {
		//Proposer d'en désapprendre une
		Utilitaire::writeInLog("Deja trops de competence");
	}
}

std::string Entite::getNom() { return nom; }
bool Entite::estVivant() {return pv > 0; }

int Entite::getPv() {
	return pv;
}
int Entite::getPvMax() {
	return stats[Stats::PV_MAX] <= STAT_MAX_EFFECTIVE ? stats[Stats::PV_MAX] : STAT_MAX_EFFECTIVE;
}
int Entite::getPm() {
	return pm;
}
int Entite::getPmMax() {
	return stats[Stats::PM_MAX] <= STAT_MAX_EFFECTIVE ? stats[Stats::PM_MAX] : STAT_MAX_EFFECTIVE;
}
int Entite::getAttaque() {
	return stats[Stats::ATK_P] <= STAT_MAX_EFFECTIVE ? stats[Stats::ATK_P] : STAT_MAX_EFFECTIVE;
}
int Entite::getAttaqueMagique() {
	return stats[Stats::ATK_M] <= STAT_MAX_EFFECTIVE ? stats[Stats::ATK_M] : STAT_MAX_EFFECTIVE;
}
int Entite::getDefence() {
	return stats[Stats::DEF_P] <= STAT_MAX_EFFECTIVE ? stats[Stats::DEF_P] : STAT_MAX_EFFECTIVE;
}
int Entite::getDefenceMagique() {
	return stats[Stats::DEF_M] <= STAT_MAX_EFFECTIVE ? stats[Stats::DEF_M] : STAT_MAX_EFFECTIVE;
}
int Entite::getVitesse() {
	return stats[Stats::VIT] <= STAT_MAX_EFFECTIVE ? stats[Stats::VIT] : STAT_MAX_EFFECTIVE;
}
std::array<int, Entite::NB_STAT>* Entite::getStats() {
	return &stats;
}
int Entite::getNbCompetence() {
	return nbCompetence;
}
Competence* Entite::getCompetence(int indice) {
	Utilitaire::testHandler(indice < nbCompetence && indice >= 0, "indice de la competence hors portée");
	return &competences[indice];
}
std::string Entite::getListCompetence() {
	std::string liste="";
	for (int i = 0; i < nbCompetence; i++) {
		liste.append(std::to_string(i + 1) +"- " + this->getCompetence(i)->toString() + "\n");
	}

	return liste;
}