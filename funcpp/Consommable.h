#pragma once
#include"Item.h"
#include"Entite.h"
#include"IUsable.h"
#include"Effets.h"
class Consommable : public Item, public IUsable
{
public:

	std::string toString();

	//constructeur de base
	Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet,std::string formule,ICiblage* ciblage,int priorite);
	
	//constructeur priorité 0
	Consommable(std::string nom,std::string description, std::function<void(Entite&, int)> effet,std::string formule,ICiblage* ciblage);
	
	//pour lire les Consommable depuis un fichier
	//utilisation d'indices
	Consommable(std::string nom, std::string description, int iEffect, std::string formule, int iCiblage, int priority);

	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite* nouvPossesseur);

	void utiliser(std::vector<Entite*> cibles);
	std::vector<Entite*> getCibles(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie);
	int getPriority();
};