#include"InputConsole.h"
#include <iostream>
#include <limits>
#include"AffichageConsole.h"
#include"Utilitaire.h"
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
	
	//utiliser des constantes pour les point et les stats initiales
	int pointADistribuer{ 25 };
	std::array<std::pair<std::string, int>, 7> stats = { {
		{"Pv", 15},
		{"Pm", 10},
		{"AtkP", 10},
		{"AtkM", 10},
		{"DefP", 10},
		{"DefM", 10},
		{"Vit", 10}
	} };

	//Afficher les stats et proposer de placer des point dans certaines catégorie
	while (pointADistribuer > 0) {
		std::string s = "Reste " + std::to_string(pointADistribuer) + " points a distribuer\n";
		for (size_t i = 0; i < stats.size(); ++i) {
			s += std::to_string(i + 1) + ". " + stats[i].first + " = " + std::to_string(stats[i].second) + "\n";
		}
		Affichage::afficher(s);

		int choix = getValidInt(1, 7, "Numero de stat invalide") - 1;
		Affichage::afficher("Rajouter combien de "+stats[choix].first +" ?\n" + std::to_string(stats[choix].second) + " + ");
		int addValue = Obtention::getValidInt(0, pointADistribuer, "Pas le bon nombre de point\nRajouter combien de " + stats[choix].first + " ?\n" + std::to_string(stats[choix].second) + " + ");
		stats[choix].second += addValue;
		pointADistribuer -= addValue;
	}
	Perso p{ "DEBUG",stats[0].second,stats[1].second,stats[2].second,stats[3].second,stats[4].second,stats[5].second,stats[6].second };
	p.apprendreCompetence(new Competence{ "attaque", "Inflige des degats", Effets::infligerDegat, "u.ap-(c.dp/4)*3", Ciblage::Mono, 0 });
	return p;
}