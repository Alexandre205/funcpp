#include "Effets.h"
#include"AffichageConsole.h"
void Effets::soinPv(Entite& cible,int puissance) {
	Affichage::afficher(cible.getNom() + " recupere ");
	cible.altererPv(puissance);
}
void Effets::soinPm(Entite& cible, int puissance) {
	Affichage::afficher(cible.getNom() + " recupere ");
	cible.altererPm(puissance);
}
void Effets::soinPvEtPm(Entite& cible, int puissance) {
	soinPv(cible, puissance);
	soinPm(cible, puissance);
}

void Effets::infligerDegat(Entite& cible, int puissance) {
	Affichage::afficher(cible.getNom() + " perd ");
	if (puissance < 1) puissance = 1;
	cible.altererPv(-puissance);
}