#include"Perso.h"
#include"Fight.h"
#include"Monstre.h"
#include"Effets.h"
#include"Consommable.h"
#include"Competence.h"
#include"Utilitaire.h"
#include"AffichageConsole.h"
#include"InputConsole.h"
#include"FileManagement.h"
#include"Salle.h"
#include"Donjon.h"
#include"DungeonGenerator.h"
#include"Ressources.h"

int main(int argc, char* argv[]) {
	Ressources::initRessources();
	Utilitaire::initSeed();
	Perso p1{ "Alex",100,10,50,50,50 };
	p1.apprendreCompetence(new Competence{ "attaque", "al", Effets::infligerDegat, "15", Ciblage::Mono, 0 });
	p1.apprendreCompetence(new Competence{ "super attaque","al",Effets::infligerDegat,"100",Ciblage::Multi,10 });
	p1.apprendreCompetence(new Competence{ "skip","al",Effets::infligerDegat,"0",Ciblage::Self,0,-1});
	p1.apprendreCompetence(new Competence{ "Suicide","al",Effets::infligerDegat,"999",Ciblage::Self,0,100});
	p1.addConsumable(new Consommable{"potion","soigne 10 pv",Effets::soinPv,"10",Ciblage::Mono,100});
	p1.addConsumable(new Consommable{"bombe","blesse les ennemis de la moitiée de leur attaque",Effets::infligerDegat,"c.ap",Ciblage::Multi,100});
	
	Donjon* d = DungeonGenerator::generateDonjon(&p1);
	d->explore();
	
	//while (true) {
	//	Donjon* d = DungeonGenerator::generateDonjon(&p1);
	//	Affichage::displayDonjon(*d);
	//	while (true) {
	//		
	//		d->move();
	//		Affichage::displayDonjon(*d);

	//	}
	//	std::cin.ignore();
	//	std::cout << "\033[2J\033[1;1H"; //clear console
	//}


	Affichage::afficher("\n\nFIN");
	return EXIT_SUCCESS;
}