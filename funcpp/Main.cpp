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


int main(int argc, char* argv[]) {
	Utilitaire::nettoyerLog();
	Perso p1{ "Alex",100,10,50,50,50 };
	MonoCible mono;
	MultiCible multi;
	Competence c1 = { "attaque","al",Effets::infligerDegat,"15",&mono,0 };
	Competence c4 = { "super attaque","al",Effets::infligerDegat,"100",&multi,10 };
	p1.apprendreCompetence(&c1);
	p1.apprendreCompetence(&c4);

	Fight f1{ &p1,FileManagement::getMonstersFromFile()};
	f1.lancerCombat();
	//std::vector<Monstre*> monstres = FileManagement::getMonstersFromFile();
	
	std::cout << "\n\nFIN";
	return EXIT_SUCCESS;
}