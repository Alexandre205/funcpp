#include<iostream>

#include "AffichageConsole.h"

void Affichage::afficher(std::string st) {
	std::cout << st;
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