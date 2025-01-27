#include<iostream>

#include"Perso.h"
#include"Salle.h"
#include"Monstre.h"
#include"erreurHandler.h"
#include"Effets.h"
#include"Potion.h"
#include"Competence.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso j{ "jean",100,100,100,100,100 };
	Competence c{"heal","soigne",Effets::soinPv,10};
	j.apprendreCompetence(&c);
	j.altererPv(-15);
	std::cout << j.toString();

	j.utiliserCompetence(0, j);

	std::cout << j.toString();
	
	return EXIT_SUCCESS;
}