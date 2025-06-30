#pragma once
#include<string>
#include<functional>
#include<vector>

#include"ICiblage.h"

class Monstre;
//interface
class IUsable {
protected:
	std::string formule;
	std::function<void(Entite&, int)> effet;
	Entite* possesseur;
	ICiblage* ciblage;
	int priorite;
public:
	virtual void utiliser(std::vector<Entite*> cibles) = 0;
	virtual std::vector<Entite*> getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) = 0;
	virtual int getPriority() = 0;
	virtual void ajouterPossesseur(Entite* nouvPossesseur) = 0;
};