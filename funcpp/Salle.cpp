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
	if (!s.compare("FightRoom")) {
		return "Fight\n";
	}
	if (!s.compare("CurrentRoom")) {
		return "Current\n";
	}
	if (!s.compare("StairsRoom")) {
		return "Stairs\n";
	}
	Utilitaire::unexpectedExit("Le type de salle n'est pas traduisible en string");
	return "";
}
Salle::Salle(){}
Salle::Salle(IStateSalle* stateSalle,int connexion) {
	setConnexion(connexion);
	setIStateSalle(stateSalle);
}
IStateSalle* Salle::getState() {
	return stateSalle;
}
void Salle::passage(Perso& joueur) {
	stateSalle->passage(joueur);
}
void Salle::addConnexion(Connexion connexion) {
	this->connexion = this->connexion | connexion;
}
void Salle::removeConnexion(Connexion connexion) {
	this->connexion = this->connexion ^ connexion;
}
void Salle::setConnexion(int connexion) {
	Utilitaire::testHandler(connexion >= 0 && connexion < 16, "La valeur entrée en parametre est invalide pour une connexion");
	this->connexion = connexion;
}
void Salle::setIStateSalle(IStateSalle* stateSalle) {
	//delete previous state if existe
	this->stateSalle = stateSalle;
}
std::string Salle::getContentString() {
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
	if (!s.compare("CurrentRoom")) {
		return "\033[0;34mC\033[0;37m";
	}
	if (!s.compare("StairsRoom")) {
		return "\033[0;32mS\033[0;37m";
	}
	Utilitaire::unexpectedExit("Le type de salle n'est pas traduisible en string");
	return "";
}
bool Salle::hasNorthConnexion() { return connexion & CONNEXION_NORTH; }
bool Salle::hasSouthConnexion() { return connexion & CONNEXION_SOUTH; }
bool Salle::hasWestConnexion() { return connexion & CONNEXION_WEST; }
bool Salle::hasEastConnexion() { return connexion & CONNEXION_EAST; }