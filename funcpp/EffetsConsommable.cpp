#include "EffetsConsommable.h"

void EffetsConsommable::soinPv(Entite& cible,int puissance) {
	cible.altererPv(puissance);
}
void EffetsConsommable::soinPm(Entite& cible, int puissance) {
	cible.altererPm(puissance);
}
void EffetsConsommable::soinPvEtPm(Entite& cible, int puissance) {
	soinPv(cible, puissance);
	soinPm(cible, puissance);
}
void EffetsConsommable::resucitePlusSoin(Entite& cible, int puissance) {
	if (!cible.estVivant()) {
		cible.altererPv(puissance);
	}
}