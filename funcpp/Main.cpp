

#include"Perso.h"
#include"Fight.h"
#include"Monstre.h"
#include"Effets.h"
#include"Consommable.h"
#include"Competence.h"
#include"AffichageConsole.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso p1{ "Alex",100,75,50,50,50 };
	Monstre m1{ "Slime",25,10,5,5,5 };
	Competence c1 = { "attaque","al",Effets::infligerDegat,"15",0 };
	Competence c2 = { "attaque","sl",Effets::infligerDegat,"15",0 };
	p1.apprendreCompetence(&c1);
	m1.apprendreCompetence(&c2);
	std::vector<Monstre*> gm1 = { &m1 };
	Fight f1{ &p1,gm1 };
	f1.lancerCombat();

	m1;
	std::cout << "\n\n FIN";
	return EXIT_SUCCESS;
}