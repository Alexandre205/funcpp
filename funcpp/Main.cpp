

#include"Perso.h"
#include"Salle.h"
#include"Monstre.h"
#include"Effets.h"
#include"Potion.h"
#include"Competence.h"
#include"AffichageConsole.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso j{ "jean",100,10,100,100,100 };
	Monstre m1{ "goblin",100,100,100,100,100 };
	Monstre m2{ "slime",100,100,100,100,100 };
	Competence c1{ "tape","fait mal",Effets::infligerDegat,"u.ap-c.dp/2",10, false};
	j.apprendreCompetence(&c1);
	j.utiliserCompetence(0, { &m1 });
	Affichage::afficher(j);

	
	return EXIT_SUCCESS;
}