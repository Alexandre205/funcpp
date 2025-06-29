#include"InputConsole.h"
#include <iostream>
#include <limits>
#include"AffichageConsole.h"
#include"Utilitaire.h"
int getValidInt(int lowerValue, int upperValue,std::string textInvalid) {
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
ActionPerforme Obtention::getActionPerforme(Entite& joueur, std::vector<Monstre*>& ennemis) {
	ActionPerforme action{ &joueur };
	std::string liste = joueur.getListCompetence();
	Affichage::afficher(liste);
	Competence* comp = joueur.getCompetence(getValidInt(1, joueur.getNbCompetence(), "Mauvais choix de competence\n" + liste) - 1);
	while (comp->getCoutPm()>joueur.getPm()) {
		Affichage::afficher("Impossible de lancer " + comp->getNom() + ", pas assez de pm\n"+liste);
		comp = joueur.getCompetence(getValidInt(1, joueur.getNbCompetence(), "Mauvais choix de competence\n" + liste) - 1);
	}
	action.action = comp;
	std::vector<Entite*> allie = { &joueur }; //permet de rajouter des Entite alliées au besoin
	action.cibles = action.action->getCibles(ennemis, allie);
	
	//liste.clear();
	//int i = 0;
	//for (i; i < ennemis.size(); i++) {
	//	liste.append(std::to_string(i+1) + " " + ennemis[i]->getNom() + "\n");
	//}
	//Affichage::afficher(liste);
	//int indiceEnnemis = getValidInt(1, (int)ennemis.size(), "Mauvais choix d\'ennemis\n" + liste)-1;

	//action.cibles = std::vector<Entite*>{ ennemis[indiceEnnemis] };

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