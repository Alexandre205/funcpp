#include "Effets.h"
#include"AffichageConsole.h"
#include"Utilitaire.h"

std::function<void(Entite&, int)> Effets::intToEffet(int i) {
	switch (i) {
	case 1: return Effets::infligerDegat;
	case 2: return Effets::soinPv;
	case 3: return Effets::soinPm;
	case 4: return Effets::soinPvEtPm;
	default: Utilitaire::unexpectedExit("Mauvais indice pour l'affectation des effets"); return NULL;
	}
}

void Effets::infligerDegat(Entite& cible, int puissance) {
	Affichage::afficher(cible.getNom() + " perd ");
	if (puissance < 1) puissance = 1;
	cible.altererPv(-puissance);
}
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

