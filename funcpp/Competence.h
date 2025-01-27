#pragma once
#include<string>
#include<functional>
class Entite;
class Competence
{
private:
	std::string nom;
	std::string description;
	std::function<void(Entite&, int)> effet;
	Entite *possesseur;
	int coutPm;
public:
	Competence();
	Competence(const Competence& competence);
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet, int coutPm);
	
	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite *nouvPossesseur);

	void utiliser(Entite& cible);
};