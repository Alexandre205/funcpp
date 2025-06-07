#pragma once
#include<string>
#include<functional>
#include<vector>

#include"IUsable.h"

class Entite;
class Monstre;
class Competence : public IUsable
{
private:
	std::string nom;
	std::string description;
	int coutPm;	
public:

	std::string toString();

	Competence();
	Competence(const Competence& competence);

	//constructeur de base
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet,std::string formuleDeDegat,ICiblage* ciblage, int coutPm,int priorite);
	
	//constructeur priorité 0
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDeDegat, ICiblage* ciblage, int coutPm);

	int getCoutPm();
	int getPriority();
	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite *nouvPossesseur);

	void utiliser(std::vector<Entite*> cibles);
	std::vector<Entite*> getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie);
};