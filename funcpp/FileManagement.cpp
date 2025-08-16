#include<iostream>
#include<fstream>

#include"FileManagement.h"
#include"Utilitaire.h"

std::vector<Monstre> FileManagement::getMonstersFromFile() {
	std::ifstream file{ NOM_FILE_MONSTRE };
	Utilitaire::testHandler(file.is_open(), "Ressource manquante Monstres.txt");
	std::vector<Monstre> monstres;
	while (!file.eof()) {
		std::string nom;
		int pv, pm, atk, atk_m, def, def_m, vit, nbGold, exp, nbComp;

		//récupere toute les informations en avance dans le fichier
		file >> nom >> pv >> pm >> atk >> atk_m >> def >> def_m >> vit >> nbGold >> exp >> nbComp;
		Utilitaire::polishMot(nom);
		Monstre monstre = Monstre{ nom,{pv,pm,atk,atk_m,def,def_m,vit},nbGold,exp };//pv,pvMax,pm,pmMax
		for (int i{ 0 }; i < nbComp; i++) {
			std::string nomComp, descriptionComp, formuleComp;
			int iEffet, iCiblage, coutPm, priorite;
			file >> nomComp >> descriptionComp >> iEffet >> formuleComp >> iCiblage >> coutPm >> priorite;
			Utilitaire::polishMot(nomComp);
			Utilitaire::polishMot(descriptionComp);
			monstre.apprendreCompetence(new Competence{ nomComp,descriptionComp,iEffet,formuleComp,iCiblage,coutPm,priorite });
		}
		monstres.push_back(monstre);
	}
	file.close();
	return monstres;
}
std::vector<Consommable> FileManagement::getConsumablesFromFile() {
	std::ifstream file{ NOM_FILE_CONSUMABLE };
	std::vector<Consommable> consumables;
	Utilitaire::testHandler(file.is_open(), "Ressource manquante Consumable.txt");

	while (!file.eof()) {
		std::string nom, description, formule;
		int price,iEffect, iCiblage, priority;
		file >> nom >> description >> price >> iEffect >> formule >> iCiblage >> priority;
		Utilitaire::polishMot(nom);
		Utilitaire::polishMot(description);
		consumables.push_back(Consommable(nom, description,price, iEffect, formule, iCiblage, priority));
	}
	file.close();
	return consumables;
}
DataEquipment FileManagement::getEquipmentFromFile() {
	std::ifstream file{ NOM_FILE_EQUIPEMENT };
	Utilitaire::testHandler(file.is_open(), "Ressource manquante Equipment.txt");
	DataEquipment data;
	
	while (!file.eof()) {
		std::string nom, description;
		int indiceTypeEquipment;
		file >> nom >> description >> indiceTypeEquipment;
		switch (indiceTypeEquipment) {
		case 1:
			int pv,pm;
			file >> pv >> pm;
			data.casques.push_back( Casque(nom,description,pv,pm));
			break;
		case 2:
			int atk,atk_m;
			file >> atk >> atk_m;
			data.armes.push_back( Arme(nom, description, atk,atk_m));
			break;
		case 3:
			int def,def_m;
			file >> def >> def_m;
			data.armures.push_back( Armure(nom, description, def,def_m));
			break;
		case 4:
			int vit;
			file >> vit;
			data.bottes.push_back( Botte(nom,description,vit));
			break;
		default:Utilitaire::unexpectedExit("Probleme avec l'indice d'équipement de " + nom);
		}
	}
	file.close();
	return data;
}
std::map<int, std::vector<Competence>> FileManagement::getPlayerCompFromFile() {
	std::ifstream file{ NOM_FILE_PLAYER_COMP };
	std::map<int, std::vector<Competence>> data;
	Utilitaire::testHandler(file.is_open(), "Ressource manquante PlayerCompetences.txt");
	while (!file.eof()) {
		std::string nom, description, formule;
		int level, iEffet, iCiblage, coutPm, priorite;
		file >> level >> nom >> description >> iEffet >> formule >> iCiblage >> coutPm >> priorite;
		Utilitaire::polishMot(nom);
		Utilitaire::polishMot(description);
		data[level].emplace_back(nom,description,iEffet,formule,iCiblage,coutPm,priorite);
	}
	file.close();
	return data;
}