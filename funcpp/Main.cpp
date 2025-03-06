

#include"Perso.h"
#include"Salle.h"
#include"Monstre.h"
#include"Effets.h"
#include"Consommable.h"
#include"Competence.h"
#include"AffichageConsole.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso j{ "jean",100,10,100,100,100 };
	j.altererPv(-50);
	Competence co1{ "soin","soigne pv",Effets::soinPv,"25",10 };
	Affichage::afficher(j);
	j.apprendreCompetence(&co1);
	j.utiliserCompetence(0,j );
	Affichage::afficher(j);

	return EXIT_SUCCESS;
}