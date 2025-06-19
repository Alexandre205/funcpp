#pragma once
#include "IStateSalle.h"
//enum SalleType {
//	Wall,
//	Empty,
//	Fight
//};
enum Connexion {
	CONNEXION_NORTH = 1, // 0001
	CONNEXION_EAST = 2, // 0010
	CONNEXION_SOUTH = 4, // 0100
	CONNEXION_WEST = 8, // 1000
	CONNEXION_NONE = 0,  // 0000
	CONNEXION_ALL = 15 // 1111
};
class Salle
{
private:
	int connexion;
	IStateSalle* stateSalle;
public:
	std::string toString();
	Salle();
	Salle(IStateSalle* stateSalle);
	void passage(Perso& joueur);
	IStateSalle* getState();
	std::string getContent();
	bool hasNotrhConnexion();
	bool hasSouthConnexion();
	bool hasWestConnexion();
	bool hasEastConnexion();
};