#include<iostream>

#include"Perso.h"
#include"Salle.h"
#include"Monstre.h"
#include"erreurHandler.h"
#include"EffetsConsommable.h"
#include"Potion.h"



int main(int argc, char* argv[]) {
	//nettoyerLog();
	Perso j{ "test",100,100,100,100,100 };
	Casque oc{ "Casque d'os","Un casque fait d'os",25,25 };
	Casque sc{ "non equipe","",0,0 };
	Potion np{ "petite potion","Une potion d'un rouge vif qui restaure la sante",EffetsConsommable::soinPv,15 };
	j.getInventaire()->ajouterConsommable(np);
	j.getInventaire()->ajouterConsommable(np);
	std::cout << j.toString();
	j.changerEquipement(oc);
	std::cout << j.toString();

	j.getInventaire()->utiliserConsommable(0,j);
	std::cout << j.toString();

	j.changerEquipement(sc);
	std::cout << j.toString();
	j.getInventaire()->utiliserConsommable(0, j);



	return EXIT_SUCCESS;
}