#pragma once

#include"Entite.h"
#include"IUsable.h"
#include"Effets.h"
#include"ILootable.h"
class Consommable : public IUsable,public ILootable
{
private:
	std::string nom;
	std::string description;
public:

	std::string toString();

	//constructeur de base
	Consommable(std::string nom,std::string description,int price, std::function<void(Entite&, int)> effet,std::string formule,Ciblage ciblage,int priorite);
	

	//obsolete
	//constructeur priorité 0
	Consommable(std::string nom,std::string description,int price, std::function<void(Entite&, int)> effet,std::string formule,Ciblage ciblage);
	
	//pour lire les Consommable depuis un fichier
	//utilisation d'indices
	Consommable(std::string nom, std::string description,int price, int iEffect, std::string formule, int iCiblage, int priority);

	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite* nouvPossesseur);

	void utiliser(std::vector<Entite*> cibles);
	std::vector<Entite*> getCibles(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie);
	int getPriority();
	std::string getNom();
	std::string getDescription();
	Ciblage getCiblage();
	int getPrice();
};