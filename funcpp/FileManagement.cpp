#include<iostream>
#include<fstream>

#include"FileManagement.h"
#include"Utilitaire.h"

std::vector<Monstre*> FileManagement::getMonstersFromFile() {
	std::ifstream file{ NOM_FILE_MONSTRE };
	std::vector<Monstre*> monstres;
	if (!file) {
		return monstres;
	}
	while (!file.eof()) {
		std::string nom;
		int pv, pm, atk, def, vit, nbComp;

		//récupere les informations toute en avance dans le fichier
		file >> nom >> pv >> pm >> atk >> def >> vit >> nbComp;
		Utilitaire::polishMot(nom);
		Monstre *monstre = new Monstre{ nom,pv,pm,atk,def,vit };
		for (int i{ 0 }; i < nbComp; i++) {
			std::string nomComp, descriptionComp, formuleComp;
			int iEffet, iCiblage, coutPm, priorite;
			file >> nomComp >> descriptionComp >> iEffet >> formuleComp >> iCiblage >> coutPm >> priorite;
			Utilitaire::polishMot(nomComp);
			Utilitaire::polishMot(descriptionComp);
			Competence* comp = new Competence{ nomComp,descriptionComp,iEffet,formuleComp,iCiblage,coutPm,priorite };
			monstre->apprendreCompetence(comp);
		}
		monstres.push_back(monstre);
	}
	file.close();
	return monstres;
}