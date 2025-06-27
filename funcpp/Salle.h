#pragma once
#include "IStateSalle.h"
#include<map>

enum SalleType {
	Wall,
	Empty,
	Battle,
	Current,
	Stairs
};
enum Connexion {
	CONNEXION_NORTH = 1, // 0001
	CONNEXION_EAST = 2, // 0010
	CONNEXION_SOUTH = 4, // 0100
	CONNEXION_WEST = 8, // 1000
	CONNEXION_NONE = 0,  // 0000
	CONNEXION_ALL = 15 // 1111
};
struct RoomInfo {
	std::string toString;
	std::string stringContent;
	IStateSalle* stateSalle;
};
class Salle
{
private:
	static std::map<SalleType, RoomInfo> infoRoom;
	SalleType roomStateType;
	int connexion;
public:
	std::string toString();
	Salle();
	Salle(SalleType stateSalle,int connexion);
	void passage(Perso& joueur);
	void addConnexion(Connexion connexion);
	void removeConnexion(Connexion connexion);
	void setConnexion(int connexion);
	void setIStateSalle(SalleType stateSalle);
	IStateSalle* getState();
	std::string getContentString();
	bool hasNorthConnexion();
	bool hasSouthConnexion();
	bool hasWestConnexion();
	bool hasEastConnexion();
};