#include "Salle.h"
#include"Utilitaire.h"
std::string Salle::toString() {
	std::string s{ typeid(*stateSalle).name() };
	s.erase(0, 6); // remove the string "class " from the type name
	if (!s.compare("EmptyRoom")) {
		return "Empty room\n";
	}
	if (!s.compare("Wall")) {
		return "Wall\n";
	}
	if (!s.compare("Fight")) {
		return "Fight\n";
	}
	Utilitaire::unexpectedExit("Le type de salle n'est pas traduisible en string");
	return "";
}
Salle::Salle(){}
Salle::Salle(IStateSalle* stateSalle) {
	connexion = CONNEXION_EAST + CONNEXION_WEST;
	this->stateSalle = stateSalle;
}
IStateSalle* Salle::getState() {
	return stateSalle;
}
void Salle::passage(Perso& joueur) {
	stateSalle->passage(joueur);
}
std::string Salle::getContent() {
	std::string s{ typeid(*stateSalle).name() };
	s.erase(0, 6); // remove the string "class " from the type name
	if (!s.compare("EmptyRoom")) {
		return " ";
	}
	if (!s.compare("Wall")) {
		return " ";
	}
	if (!s.compare("FightRoom")) {
		return "\033[0;31mF\033[0;37m";
	}
	Utilitaire::unexpectedExit("Le type de salle n'est pas traduisible en string");
	return "";
}

bool Salle::hasNotrhConnexion() { return connexion & CONNEXION_NORTH; }
bool Salle::hasSouthConnexion() { return connexion & CONNEXION_SOUTH; }
bool Salle::hasWestConnexion() { return connexion & CONNEXION_WEST; }
bool Salle::hasEastConnexion() { return connexion & CONNEXION_EAST; }