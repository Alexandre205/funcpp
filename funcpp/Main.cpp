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

	/*FightRoom f;
	f.passage(p1);

	Monstre m1{ "LoupS",10,10,10,10,10 };
	m1.apprendreCompetence(new Competence("Coup de griffe", "lo", Effets::infligerDegat, "10", Ciblage::Mono, 0));

	Monstre m2 = m1;*/
	//std::cout<<m2.getCompetence(0)->toString();

	Affichage::afficher("\n\nFIN");
	return EXIT_SUCCESS;
}