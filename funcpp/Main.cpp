#include<iostream>

#include"Perso.h"
#include"Salle.h"
#include"Monstre.h"
#include"Effets.h"
#include"Potion.h"
#include"Competence.h"


int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso j{ "jean",100,100,10,100,100 };
	Monstre m1{ "goblin",100,100,100,100,100 };
	Monstre m2{ "slime",100,100,100,100,100 };
	Competence c{ "tape","fait mal",Effets::infligerDegat,"u.ap-c.dp/2",10, false};
	j.apprendreCompetence(&c);
	
	std::cout << m1.toString() + "\n" + m2.toString() + "\n";
	j.utiliserCompetence(0, { &m1,&m2 });
	std::cout << m1.toString() +"\n" +m2.toString()+"\n"+j.toString();

	
	return EXIT_SUCCESS;
}