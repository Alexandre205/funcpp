#include"Salle.h"
#include"IStateSalle.h"
#include"Utilitaire.h"

std::map< SalleType,RoomInfo> Salle::infoRoom = {
	{SalleType::Empty   ,{"Empty room\n"," ",new EmptyRoom}},
	{SalleType::Wall    ,{"Wall\n"," ",new WallRoom}},
	{SalleType::Battle  ,{"Figth\n","\033[0;31mF\033[0;37m",new FightRoom}},
	{SalleType::Current ,{"Current\n","\033[0;34mP\033[0;37m",new CurrentRoom}},
	{SalleType::Stairs  ,{"Stairs\n","\033[0;32mS\033[0;37m",new StairsRoom}},
	{SalleType::Chest   ,{"Chess\n","\033[0;33mC\033[0;37m", new ChestRoom}},
	{SalleType::Merchant,{"Merchant\n","\033[0;36mM\033[0;37m", new MerchantRoom}}
};
std::string Salle::toString() {
	return infoRoom[roomStateType].toString;
}
Salle::Salle(){}
Salle::Salle(SalleType stateSalle,int connexion) {
	setConnexion(connexion);
	setIStateSalle(stateSalle);
}
IStateSalle* Salle::getState() {
	return infoRoom[roomStateType].stateSalle;
}
void Salle::passage(Perso& joueur) {
	infoRoom[roomStateType].stateSalle->passage(joueur);
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
void Salle::setIStateSalle(SalleType stateSalle) {
	this->roomStateType = stateSalle;
}
std::string Salle::getContentString() {
	return infoRoom[roomStateType].stringContent;
}
bool Salle::hasNorthConnexion() { return connexion & CONNEXION_NORTH; }
bool Salle::hasSouthConnexion() { return connexion & CONNEXION_SOUTH; }
bool Salle::hasWestConnexion() { return connexion & CONNEXION_WEST; }
bool Salle::hasEastConnexion() { return connexion & CONNEXION_EAST; }
bool Salle::isState(SalleType stateRoom) {
	return stateRoom == roomStateType;
}