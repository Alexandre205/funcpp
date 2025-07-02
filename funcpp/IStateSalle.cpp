#include"IStateSalle.h"
#include"Fight.h"
#include"FileManagement.h"
#include"AffichageConsole.h"
#include"Utilitaire.h"
#include"InputConsole.h"

void WallRoom::passage(Perso& joueur) {
	Utilitaire::unexpectedExit("Mur traversé, pas normal");
}
void EmptyRoom::passage(Perso& joueur) {
	Affichage::afficher("Vous entrez dans une salle vide et rien ne se passe\n");
}
void FightRoom::passage(Perso& joueur) {
	//à remplacer par une selection un peu mieux des monstres genre pas d'acces direct au fichier + monstres aléatoire
	std::vector<Monstre*> ennemis = FileManagement::getMonstersFromFile();
	std::string listeMonstre{"Vous entrez dans une salle avec des monstres \n"};
	for (Monstre* ennemi : ennemis) {
		listeMonstre.append(ennemi->toString()+"\n");
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
void ChestRoom::passage(Perso& joueur) {
	//code d'ouverture de coffre;
	Affichage::afficher("Il y a un coffre. Voulez-vous l'ouvrire\n1.Oui\n2.Non\n");
	int i = Obtention::getValidInt(1, 2, "Nombre invalide");
	if (i == 1) {
		Consommable *c = new Consommable{ "potion","soigne 10 pv",Effets::soinPv,"10",Ciblage::Mono,100 };
		Affichage::afficher("Vous trouvez une " + c->getNom() + ".\n");
		joueur.addConsumable(c);
	}
	else {
		Affichage::afficher("Vous laisser le coffre là");
	}
}
void MerchantRoom::passage(Perso& joueur) {
	//code du marchand
	Affichage::afficher("Il y a un marchand\n");
}