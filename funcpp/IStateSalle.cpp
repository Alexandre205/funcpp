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

ChestRoom::ChestRoom()
	: tresor{ Ressources::dataConsommable.at(Utilitaire::getGeneratedInteger(0, (int)Ressources::dataConsommable.size() - 1))}
{}
void ChestRoom::passage(Perso& joueur) {
	//code d'ouverture de coffre;
	Affichage::afficher("Il y a un coffre. Voulez-vous l'ouvrire\n1.Oui\n2.Non\n");
	int i = Obtention::getValidInt(1, 2, "Nombre invalide");
	if (i == 1) {
		
		Affichage::afficher("Vous trouvez une " + tresor.getNom() + ".\n");
		joueur.addConsumable(new Consommable(tresor));
	}
	else {
		Affichage::afficher("Vous laisser le coffre là");
	}
}
void MerchantRoom::passage(Perso& joueur) {
	//code du marchand
	Affichage::afficher("Il y a un marchand\n");
}