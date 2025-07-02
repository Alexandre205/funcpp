#pragma once
#include<string>
#include<functional>
#include<vector>
#include<array>

#include"ICiblage.h"

class Monstre;

enum Ciblage {
	Mono, Multi, Self
};
struct CiblageInfo {
	std::string stringCiblage;
	ICiblage* ciblage;
};
//interface
class IUsable {
	
protected:
	std::string formule;
	std::function<void(Entite&, int)> effet;
	Entite* possesseur;
	Ciblage ciblage;
	int priorite;
public:
	static std::array<CiblageInfo, 3> infoCiblage;
	virtual void utiliser(std::vector<Entite*> cibles) = 0;
	virtual std::vector<Entite*> getCibles(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie) = 0;
	virtual int getPriority() = 0;
	virtual void ajouterPossesseur(Entite* nouvPossesseur) = 0;
	virtual Ciblage getCiblage() = 0;
};