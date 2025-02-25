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
	std::function<void(Entite&, int)> effet;
	std::string formuleDeDegat;
	Entite *possesseur;
	int coutPm;
	bool multiCible;

	void utiliser(Entite& cible);
public:

	std::string toString();

	Competence();
	Competence(const Competence& competence);
	Competence(std::string nom, std::string description, std::function<void(Entite&, int)> effet,std::string formuleDeDegat, int coutPm, bool multiCible);
	
	// toujours appelé quand competence attaché à Entite
	void ajouterPossesseur(Entite *nouvPossesseur);

	//void utiliser(Entite& cible);
	void utiliser(std::vector<Entite*> cibles);
};