#include"ICiblage.h"
#include"Utilitaire.h"
#include"InputConsole.h"
ICiblage* ICiblage::intToICiblage(int i) {
	switch (i) {
	case 1:return new MonoCible;
	case 2: return new MultiCible;
	case 3:return new SelfCible;
	default:Utilitaire::unexpectedExit("Mauvais indice pour l'affectation du ciblage"); return NULL;
	}
}
//void MonoCible::appliquerEffet(std::function<void(Entite&, int)>effet, std::vector<Entite*>& cibles, Entite& lanceur,std::string formuleDegat) {
//	int valeurAjoute = Utilitaire::applicationFormuleDeDegat(formuleDegat, lanceur, *cibles[0]);
//	effet(*cibles[0],valeurAjoute);
//}
std::vector<Entite*> MonoCible::selectionnerCible(std::vector<Monstre*>& ennemis,std::vector<Entite*>& allie){
	std::vector<Entite*> cibles;
	for (Entite* ennemi : ennemis) {
		cibles.push_back(ennemi);
	}
	return { ennemis.at(Obtention::getCibleIndice(cibles)) };
}

//void MultiCible::appliquerEffet(std::function<void(Entite&, int)>effet, std::vector<Entite*>& cibles, Entite& lanceur, std::string formuleDegat) {
//	for (Entite* cible : cibles) {
//		int valeurAjoute = Utilitaire::applicationFormuleDeDegat(formuleDegat, lanceur, *cible);
//		effet(*cible, valeurAjoute);
//	}
//}
std::vector<Entite*> MultiCible::selectionnerCible(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) {
	//conversion de vector<Monstre*> en vector<Entite*>
	std::vector<Entite*> cibles;
	for (Entite* ennemi : ennemis) {
		cibles.push_back(ennemi);
	}
	return cibles;
}

// à changer si on rajoute des alliers
std::vector<Entite*> SelfCible::selectionnerCible(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) {
	return { allie[0] };
}