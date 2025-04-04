#include"InputConsole.h"
#include"AffichageConsole.h"
int getValidInt(int lowerValue, int upperValue,std::string textInvalid) {
	int nb = -1;
	std::cin >> nb;
	while (nb<lowerValue || nb>upperValue) {
		Affichage::afficher(textInvalid);
		std::cin >> nb;
	}
	return nb;
}
ActionPerforme Obtention::getActionPerforme(Entite& joueur, std::vector<Monstre*>& ennemis) {
	ActionPerforme action{ &joueur };
	std::string liste = joueur.getListCompetence();
	Affichage::afficher(liste);
	action.action = joueur.getCompetence(getValidInt(1,joueur.getNbCompetence(), "Mauvais choix de competence\n" + liste)-1);
	
	// gestion uniquement mono // améliorer plus tard
	liste.clear();
	int i = 0;
	for (i; i < ennemis.size(); i++) {
		liste.append(std::to_string(i+1) + " " + ennemis[i]->getNom() + "\n");
	}
	Affichage::afficher(liste);
	int indiceEnnemis = getValidInt(1, (int)ennemis.size(), "Mauvais choix d\'ennemis\n" + liste)-1;

	action.cibles = std::vector<Entite*>{ ennemis[indiceEnnemis] };

	return action;
}