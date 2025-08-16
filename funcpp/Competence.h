#pragma once
#include<string>
#include<functional>
#include<vector>

#include"IUsable.h"

class Entite;

class Competence : public IUsable
{
private:
	std::string nom;
	std::string description;
	int coutPm;


public:

	std::string toString();

	Competence();
	//Competence(const Competence& competence);

	//constructeur de base
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet,std::string formuleDeDegat, Ciblage ciblage, int coutPm,int priorite);
	
	//constructeur priorité 0
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, std::string formuleDeDegat, Ciblage ciblage, int coutPm);

	//pour lire les competence depuis un fichier
	//utilisation d'indices
	Competence(std::string nom, std::string description, int iEffet, std::string formule, int iICiblage, int coutPm, int priorite);

	int getCoutPm();
	int getPriority();
	std::string getNom();
	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite *nouvPossesseur);

	void utiliser(std::vector<Entite*> cibles);
	std::vector<Entite*> getCibles(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie);

	Ciblage getCiblage();
};