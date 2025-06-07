

#include"Perso.h"
#include"Fight.h"
#include"Monstre.h"
#include"Effets.h"
#include"Consommable.h"
#include"Competence.h"
#include"Utilitaire.h"
#include"AffichageConsole.h"
#include"InputConsole.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso p1{ "Alex",100,10,50,50,50 };
	Monstre m1{ "Slime",101,10,5,5,5 };
	Monstre m2{ "Slime1",25,10,5,5,5 };
	MonoCible mono;
	MultiCible multi;
	Competence c1 = { "attaque","al",Effets::infligerDegat,"15",&mono,0 };
	Competence c2 = { "attaque","sl1",Effets::infligerDegat,"15",&mono,0 };
	Competence c3 = { "attaque","sl3",Effets::infligerDegat,"15",&mono,0 };
	Competence c4 = { "super attaque","al",Effets::infligerDegat,"100",&multi,10 };
	p1.apprendreCompetence(&c1);
	p1.apprendreCompetence(&c4);
	m1.apprendreCompetence(&c2);
	m2.apprendreCompetence(&c3);
	std::vector<Monstre*> gm1 = { &m1,&m2 };
	Fight f1{ &p1,gm1 };
	f1.lancerCombat();

	std::cout << "\n\nFIN";
	return EXIT_SUCCESS;
}