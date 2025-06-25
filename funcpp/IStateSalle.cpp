#include "IStateSalle.h"
#include"Fight.h"
#include"FileManagement.h"
#include"AffichageConsole.h"
#include"Utilitaire.h"

void Wall::passage(Perso& joueur) {
	Utilitaire::unexpectedExit("Mur traversé, pas normal");
}
void EmptyRoom::passage(Perso& joueur) {
	Affichage::afficher("Vous entrez dans une salle vide et rien ne se passe\n");
}
void FightRoom::passage(Perso& joueur) {
	//à remplacer par une selection un peu mieux des monstres genre pas d'acces au fichier + monstres aléatoire
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
	Affichage::afficher("Bravo " + joueur.getNom() + ", vous etes sorti.\n");
}