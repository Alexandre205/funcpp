#include"IStateSalle.h"
#include"Fight.h"
#include"FileManagement.h"
#include"AffichageConsole.h"
#include"Utilitaire.h"
#include"InputConsole.h"
#include"Ressources.h"
#include"Consommable.h"

void WallRoom::passage(Perso& joueur) {
	Utilitaire::unexpectedExit("Mur traversé, pas normal");
}
void EmptyRoom::passage(Perso& joueur) {
	Affichage::afficher("Vous entrez dans une salle vide et rien ne se passe\n");
}

FightRoom::FightRoom() {
	std::vector<Monstre> m = Ressources::dataMonsters;
	for (Monstre ennemi : m) {
		ennemis.push_back(ennemi);
	}
}
void FightRoom::passage(Perso& joueur) {
	
	std::string listeMonstre{"Vous entrez dans une salle avec des monstres\n"};
	for (Monstre ennemi : ennemis) {
		listeMonstre.append(ennemi.toString()+"\n");
	}
	listeMonstre.append("Que faite vous ?\n");
	Affichage::afficher(listeMonstre);

	Fight f{ &joueur, ennemis };
	f.lancerCombat();
}
void CurrentRoom::passage(Perso& joueur) {
	Affichage::afficher("Vous ne bougez pas et rien ne se passe\n");
}
void StairsRoom::passage(Perso& joueur) {
	Affichage::afficher("Oh mon Dieu, la sortie\n");
}

//faire en sorte que certain equipement puissent etre présent aussi
ChestRoom::ChestRoom()
	: tresor{ Ressources::dataConsommable.at(Utilitaire::getGeneratedInteger(0, (int)Ressources::dataConsommable.size() - 1))}
{}
void ChestRoom::passage(Perso& joueur) {
	//code d'ouverture de coffre;
	std::vector<Consommable> d = Ressources::dataConsommable;

	Affichage::afficher("Il y a un coffre. Voulez-vous l'ouvrire\n1.Oui\n2.Non\n");
	int i = Obtention::getValidInt(1, 2, "Nombre invalide\n");
	if (i == 1) {
		
		Affichage::afficher("Vous trouvez une " + tresor.getNom() + ".\n");
		joueur.addConsumable(new Consommable(tresor));
	}
	else {
		Affichage::afficher("Vous laisser le coffre la\n");
	}
}

MerchantRoom::MerchantRoom() {
	listeItem = Ressources::dataConsommable;
}
void MerchantRoom::passage(Perso& joueur) {
	//code du marchand
	std::string s{ "Il y a un marchand\n" };
	int choice;
	int listeItemSize;
	do{
		s.append("Fond actuel : " + std::to_string(joueur.getNbGold())+"\n");
		int i;
		listeItemSize = (int)listeItem.size();
		for (i = 0; i < listeItemSize; i++) {
			s.append(std::to_string(i + 1) + ". " + listeItem[i].getNom() + " (" + std::to_string(listeItem[i].getPrice()) + " golds)\n");
		}
		s.append(std::to_string(i + 1) + ". Quitter le shop.\n");
		Affichage::afficher(s);
		s.clear();
		choice = Obtention::getValidInt(1, listeItemSize +1,"Nombre invalide\n");
		if (choice != listeItemSize + 1) {
			if (listeItem[choice - 1].getPrice() > joueur.getNbGold()) {
				Affichage::afficher("Fond insuffisant.\n");
			}
			else {
				joueur.modifyNbGold(-listeItem[choice - 1].getPrice());
				joueur.addConsumable(new Consommable(listeItem[choice - 1]));
				listeItem.erase(listeItem.begin() + (choice - 1));
			}
		}
	} while (choice != listeItemSize + 1);
}