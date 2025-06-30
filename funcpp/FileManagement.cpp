#include<iostream>
#include<fstream>

#include"FileManagement.h"
#include"Utilitaire.h"

std::vector<Monstre*> FileManagement::getMonstersFromFile() {
	std::ifstream file{ NOM_FILE_MONSTRE };
	std::vector<Monstre*> monstres;
	Utilitaire::testHandler(file.is_open(), "Ressource manquante Monstres.txt");
	
	while (!file.eof()) {
		std::string nom;
		int pv, pm, atk, def, vit, nbComp;

		//récupere toute les informations en avance dans le fichier
		file >> nom >> pv >> pm >> atk >> def >> vit >> nbComp;
		Utilitaire::polishMot(nom);
		Monstre *monstre = new Monstre{ nom,pv,pm,atk,def,vit };
		for (int i{ 0 }; i < nbComp; i++) {
			std::string nomComp, descriptionComp, formuleComp;
			int iEffet, iCiblage, coutPm, priorite;
			file >> nomComp >> descriptionComp >> iEffet >> formuleComp >> iCiblage >> coutPm >> priorite;
			Utilitaire::polishMot(nomComp);
			Utilitaire::polishMot(descriptionComp);
			monstre->apprendreCompetence(new Competence{ nomComp,descriptionComp,iEffet,formuleComp,iCiblage,coutPm,priorite });
		}
		monstres.push_back(monstre);
	}
	file.close();
	return monstres;
}
std::vector<Consommable*> FileManagement::getConsumablesFromFile() {
	std::ifstream file{ NOM_FILE_CONSUMABLE };
	std::vector<Consommable*> consumables;
	Utilitaire::testHandler(file.is_open(), "Ressource manquante Consumable.txt");

	while (!file.eof()) {
		std::string nom, description, formule;
		int iEffect, iCiblage, priority;
		file >> nom >> description >> iEffect >> formule >> iCiblage >> priority;
		Utilitaire::polishMot(nom);
		Utilitaire::polishMot(description);
		consumables.push_back(new Consommable(nom, description, iEffect, formule, iCiblage, priority));
	}
	return consumables;
}