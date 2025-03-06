#pragma once
#include<string>
#include<functional>
#include<vector>

class Entite;
//interface
class IUsable {
protected:
	//surement une enum pour les specification de l'utilisation, ex:multicible,prio,...
	std::string formule;
	std::function<void(Entite&, int)> effet;
	Entite* possesseur;
public:
	virtual void utiliser(Entite& cible) = 0;
	//virtual void utiliser(std::vector<Entite*> cibles) = 0;
};