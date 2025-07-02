#include"ICiblage.h"
#include"Utilitaire.h"
#include"InputConsole.h"
Ciblage ICiblage::intToICiblage(int i) {
	return (Ciblage)(i - 1);
}


std::vector<Entite*> MonoCible::selectionnerCible(std::vector<Entite*>& ennemis,std::vector<Entite*>& allie){
	std::vector<Entite*> cibles;
	for (Entite* ennemi : ennemis) {
		cibles.push_back(ennemi);
	}
	return { ennemis.at(Obtention::getCibleIndice(cibles)) };
}

std::vector<Entite*> MultiCible::selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie) {
	//conversion de vector<Monstre*> en vector<Entite*>
	std::vector<Entite*> cibles;
	for (Entite* ennemi : ennemis) {
		cibles.push_back(ennemi);
	}
	return cibles;
}

// à changer si on rajoute des allies
std::vector<Entite*> SelfCible::selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie) {
	return { allie[0] };
}


