#include"Salle.h"
#include"Utilitaire.h"
#include<vector>

std::string Salle::toSring() {
	return std::to_string(numero) + " " + listeMonstrePresent();
}

Salle::Salle(int numero, Monstre ennemis[NB_MONSTRE_MAX]) :numero{ numero } {
	this->nbMonstre = 0;
	int i = 0;
	while (i < NB_MONSTRE_MAX && ennemis[i].estInitialis()) {
		AddEnnemis(ennemis[i]);
		i++;
	}
}

void Salle::AddEnnemis(Monstre ennemi) {
	if (nbMonstre < NB_MONSTRE_MAX) {
		ennemis[nbMonstre] = ennemi;
		nbMonstre++;
	}
	else {
		Utilitaire::writeInLog("Plus d'espace pour faire apparaitre un nouveau monstre");
	}
}
std::string Salle::listeMonstrePresent() {
	std::string liste = "";
	for (int i = 0; i < nbMonstre; i++) {
		liste += std::to_string(i+1) + "." + ennemis[i].getNom() + "\n";
	}
	return liste;
}