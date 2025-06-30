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

int main(int argc, char* argv[]) {
	Utilitaire::initSeed();
	Perso p1{ "Alex",100,10,50,50,50 };
	p1.apprendreCompetence(new Competence{ "attaque", "al", Effets::infligerDegat, "15", new MonoCible(), 0 });
	p1.apprendreCompetence(new Competence{ "super attaque","al",Effets::infligerDegat,"100",new MultiCible(),10 });
	Consommable c1{"potion","soigne 10 pv",Effets::soinPv,"10",new SelfCible,100};
	Consommable c2{"bombe","blesse les ennemis de la moitiée de leur attaque",Effets::infligerDegat,"c.ap",new MultiCible,100};
	p1.addConsumable(c1);
	p1.addConsumable(c2);
	
	std::vector<Consommable*> c = FileManagement::getConsumablesFromFile();
	c;
	int i = 1;
	while (true) {
		Donjon* d = DungeonGenerator::generateDonjon(&p1);
		Affichage::displayDonjon(*d);
		while (true) {
			
			d->move();
			Affichage::displayDonjon(*d);

		}
		std::cin.ignore();
		std::cout << "\033[2J\033[1;1H"; //clear console
	}


	Affichage::afficher("\n\nFIN");
	return EXIT_SUCCESS;
}