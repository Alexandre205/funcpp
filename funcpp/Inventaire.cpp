#include "Inventaire.h"

std::string Inventaire::toString() {
	std::string retour = "";
	retour += casque.toString();
	retour += arme.toString();
	retour += armure.toString();
	retour += botte.toString();
	for (int i = 0; i < nbConsommable; i++) {
		retour += inventaire[i]->toString();
	}
	return retour;
}

Inventaire::Inventaire() :nbConsommable{ 0 }, tailleInventaire(TAILLE_DE_BASE_INVENTAIRE),
	casque{ "non equipe","",0,0 },
	arme{ "non equipe", "", 0 },
	armure{ "non equipe","",0 },
	botte{ "non equipe","",0 } {
	inventaire.fill(NULL);
}


void Inventaire::ajouterConsommable(Consommable& nouvConso) {
	if (nbConsommable < TAILLE_DE_BASE_INVENTAIRE) {
		inventaire[nbConsommable] = &nouvConso;
		nbConsommable++;
	}
	else {
		// 1.checker extra inventaire
		// 2.proposer de supprimer un objet
	}
}
void Inventaire::supprimerConsommable(int indiceConso) {
	testHandler(indiceConso < nbConsommable, "indice de suppression hors portee", false);
	for (int i = indiceConso; i < nbConsommable - 1; i++) {
		inventaire[i] = inventaire[i + 1];
	}
	nbConsommable--;
}
void Inventaire::utiliserConsommable(int indiceConso,Entite& cible) {
	testHandler(indiceConso < nbConsommable, "indice d'utilisation hors portee", false);
	inventaire[indiceConso]->utilisation(cible);
	supprimerConsommable(indiceConso);
}

void Inventaire::ajouterEquipement(Casque casque) {
	this->casque = casque;
}
void Inventaire::ajouterEquipement(Arme arme){
	this->arme = arme;
}
void Inventaire::ajouterEquipement(Armure armure){
	this->armure = armure;
}
void Inventaire::ajouterEquipement(Botte botte){
	this->botte = botte;
}

Casque Inventaire::getCasque() {
	return casque;
}
Arme Inventaire::getArme() {
	return arme;
}
Armure Inventaire::getArmure() {
	return armure;
}
Botte Inventaire::getBotte() {
	return botte;
}