#include<iostream>

#include "AffichageConsole.h"

void Affichage::afficher(std::string st) {
	std::cout << st;
}
void Affichage::afficher(std::vector<Entite*>& ens) {
	std::string liste{ "" };
	for (int i = 0; i < ens.size();i++) {
		liste.append(std::to_string(i+1) + "." + ens[i]->getNom() + " (" + std::to_string(ens[i]->getPv()) + "/" + std::to_string(ens[i]->getPvMax()) + ")" + "\n");
	}
	std::cout << liste;
}
void Affichage::afficher(Entite& en) {
	std::cout << en.toString()+"\n";
}
void Affichage::afficher(Item& it) {
	std::cout << it.toString()+"\n";
}
void Affichage::afficher(Competence& co) {
	std::cout << co.toString() + "\n";
}
void Affichage::afficher(Inventaire* in) {
	std::cout << in->toString()+"\n";
}
void Affichage::afficher(Inventaire& in) {
	std::cout << in.toString()+"\n";
}
void Affichage::afficher(Perso& pe) {
	std::cout << pe.toString()+"\n";
}
void Affichage::afficher(Fight& fi) {
	std::cout << fi.toSring();
}