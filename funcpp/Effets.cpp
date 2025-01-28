#include "Effets.h"

void Effets::soinPv(Entite& cible,int puissance) {
	cible.altererPv(puissance);
}
void Effets::soinPm(Entite& cible, int puissance) {
	cible.altererPm(puissance);
}
void Effets::soinPvEtPm(Entite& cible, int puissance) {
	soinPv(cible, puissance);
	soinPm(cible, puissance);
}
void Effets::resucitePlusSoin(Entite& cible, int puissance) {
	if (!cible.estVivant()) {
		cible.altererPv(puissance);
	}
}
void Effets::infligerDegat(Entite& cible, int puissance) {
	cible.altererPv(-puissance);
}