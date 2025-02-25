#pragma once
#include<string>
#include<functional>
#include<vector>

class Entite;
//interface
class IUsable {
	//surement une enum pour les specification de l'utilisation, ex:multicible,prio,...
	std::string formuleDegat;
	std::function<void(Entite&, int)> effet;
	Entite* possesseur;

	IUsable(std::string formuleDegat, std::function<void(Entite&, int)> effet, Entite* possesseur);
	~IUsable();
	virtual void utiliser(Entite& cible) = 0;
	virtual void utiliser(std::vector<Entite*> cibles) = 0;
};