#pragma once
#include "IStateSalle.h"
//enum SalleType {
//	Wall,
//	Empty,
//	Fight
//};
class Salle
{
private:
	IStateSalle* stateSalle;
public:
	std::string toString();
	Salle();
	Salle(IStateSalle* stateSalle);
	void passage(Perso& joueur);
	IStateSalle* getState();
	std::string getContent();
};