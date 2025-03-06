

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
	Consommable co1{ "potion","soigne pv",Effets::soinPv,"25",&j };
	Affichage::afficher(j);
	j.getInventaire()->ajouterConsommable(co1);
	j.getInventaire()->utiliserConsommable(0,j);
	Affichage::afficher(j);

	return EXIT_SUCCESS;
}