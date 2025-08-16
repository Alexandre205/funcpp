#include"InputConsole.h"
#include <iostream>
#include <limits>
#include"AffichageConsole.h"
#include"Utilitaire.h"
#include"Ressources.h"

int Obtention::getValidInt(int lowerValue, int upperValue,std::string textInvalid) {
	int nb = -1;
	std::cin >> nb;
	while (std::cin.fail() || nb<lowerValue || nb>upperValue) {
		Affichage::afficher(textInvalid);
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> nb;
	}
	return nb;
}
ActionPerforme Obtention::getActionPerforme(Perso& joueur, std::vector<Entite*>& ennemis) {
	ActionPerforme action{ &joueur };
	std::string liste = joueur.getListCompetence();
	int plusOneIfItems = 0;
	if (joueur.getInventaire()->getNbConsommable() > 0) {
		plusOneIfItems = 1;
		liste.append(std::to_string(joueur.getNbCompetence() + 1) + "- Utiliser un objet.\n");
	}
	Affichage::afficher(liste);

	int choix = getValidInt(1, joueur.getNbCompetence() + plusOneIfItems, "Mauvais choix de competence\n" + liste) - 1;
	while (choix < joueur.getNbCompetence() && joueur.getCompetence(choix)->getCoutPm() > joueur.getPm()) {
		Affichage::afficher("Impossible de lancer " + joueur.getCompetence(choix)->getNom() + ", pas assez de pm\n" + liste);
		choix = getValidInt(1, joueur.getNbCompetence() + plusOneIfItems, "Mauvais choix de competence\n" + liste) - 1;
	}
	if (choix < joueur.getNbCompetence()) {
		//utiliser la competence choisie
		Competence* comp = joueur.getCompetence(choix);
		action.action = comp;
		std::vector<Entite*> allie = { &joueur }; //permetra de rajouter des Entite alliées au besoin
		action.cibles = action.action->getCibles(ennemis, allie);
	}
	else {
		//utiliser un objets
		liste.clear();
		liste.append(joueur.getInventaire()->getConsumableList());
		Affichage::afficher(liste);

		int choixObjet = getValidInt(1, joueur.getInventaire()->getNbConsommable() + plusOneIfItems, "Mauvais choix d'objet\n" + liste) - 1;
		action.action = joueur.getInventaire()->getConsumable(choixObjet);
		joueur.getInventaire()->supprimerConsommable(choixObjet);
		std::vector<Entite*> allie = { &joueur };
		action.cibles = action.action->getCibles(ennemis, allie);
	}
	Affichage::clear();
	return action;
}
int Obtention::getCibleIndice(std::vector<Entite*>& cibles) {
	Affichage::afficher(cibles);
	return getValidInt(1,(int)cibles.size(),"Cible impossible")-1;
}
Direction Obtention::getDirection(Salle* salle) {
	std::array<Direction, 4> directionPossible;
	std::string s{"Ou voulez aller ?\n"};
	int numConnexion = 1;
	if (salle->hasNorthConnexion()) {
		s.append(std::to_string(numConnexion) + ".Nord\n");
		directionPossible[numConnexion - 1] = Direction::NORTH;
		numConnexion++;
	}
	if (salle->hasSouthConnexion()) {
		s.append(std::to_string(numConnexion) + ".Sud\n");
		directionPossible[numConnexion - 1] = Direction::SOUTH;
		numConnexion++;
	}
	if (salle->hasWestConnexion()) {
		s.append(std::to_string(numConnexion) + ".Ouest\n");
		directionPossible[numConnexion - 1] = Direction::WEST;
		numConnexion++;
	}
	if (salle->hasEastConnexion()) {
		s.append(std::to_string(numConnexion) + ".Est\n");
		directionPossible[numConnexion - 1] = Direction::EAST;
		numConnexion++;
	}
	Utilitaire::testHandler(numConnexion > 1, "Pas de connxion dans la salle");
	Affichage::afficher(s);
	return directionPossible[getValidInt(1, numConnexion-1, "Impossible d'aller par la\n")-1];
}
Perso Obtention::getNewStartPerso() {
	//recup nom
	
	std::string nom;
	Affichage::afficher("Choisissez un nom\n");
	std::getline(std::cin, nom);
	//utiliser des constantes pour les point et les stats initiales
	int pointADistribuer{ 25 };
	std::array<int, Entite::NB_STAT> stats = {15,10,10,10,10,10,10};
	Affichage::afficher("Distribution des stats\n");

	//Afficher les stats et proposer de placer des point dans certaines catégorie
	while (pointADistribuer > 0) {
		std::string s = "Reste " + std::to_string(pointADistribuer) + " points a distribuer\n";
		for (int i = 0; i < Entite::NB_STAT; ++i) {
			s += std::to_string(i + 1) + ". " + Entite::statToString[i] + " = " + std::to_string(stats[i]) + "\n";
		}
		Affichage::afficher(s);//faut pas afficher pmMax et pvMax

		int choix = getValidInt(1, Entite::NB_STAT, "Numero de stat invalide") - 1;
		Affichage::afficher("Rajouter combien de "+ Entite::statToString[choix] +" ?\n" + std::to_string(stats[choix]) + " + ");
		int addValue = Obtention::getValidInt(0, pointADistribuer, "Pas le bon nombre de point\nRajouter combien de " + Entite::statToString[choix] + " ?\n" + std::to_string(stats[choix]) + " + ");
		stats[choix] += addValue;
		pointADistribuer -= addValue;
	}
	Perso p{ nom,stats};
	p.apprendreCompetence(new Competence{ Ressources::dataPlayerComp[0][0] });

	;
	std::string s = "Choisissez une competence\n";
	for (int i{ 0 }; i < Ressources::dataPlayerComp[1].size(); i++) {
		s.append(std::to_string(i+1) + "." + Ressources::dataPlayerComp[1][i].toString() + "\n");
	}
	Affichage::afficher(s);
	int choix = getValidInt(1, (int)Ressources::dataPlayerComp[1].size(), "Mauvais choix de competence");
	p.apprendreCompetence(new Competence(Ressources::dataPlayerComp[1][choix-1]));
	Affichage::clear();
	return p;
}