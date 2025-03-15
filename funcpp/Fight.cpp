#include<algorithm>

#include"Fight.h"
#include"Utilitaire.h"
#include"IUsable.h"

std::string Fight::toSring() {
	return listeMonstrePresent();
}

Fight::Fight(Perso* joueur, std::vector<Monstre*> ennemis) :joueur{ joueur } {
	this->nbMonstre = 0;
	int i = 0;
	while (i < NB_MONSTRE_MAX && i<ennemis.size()) {
		AddEnnemis(ennemis[i]);
		i++;
	}
}

void Fight::AddEnnemis(Monstre* ennemi) {
	if (nbMonstre < NB_MONSTRE_MAX) {
		ennemis.push_back(ennemi);
		nbMonstre++;
	}
	else {
		Utilitaire::writeInLog("Plus d'espace pour faire apparaitre un nouveau monstre");
	}
}
std::string Fight::listeMonstrePresent() {
	std::string liste = "";
	for (int i = 0; i < nbMonstre; i++) {
		liste += std::to_string(i+1) + "." + ennemis[i]->getNom() + "\n";
	}
	return liste;
}

bool Fight::isFinished() {
	if (!joueur->estVivant()) {
		return true;
	}
	int i{ 0 };
	while (i<nbMonstre && !ennemis[0]->estVivant()) {
		i++;
	}
	return i == nbMonstre;
}
void Fight::majOrdreDAction(std::deque<Entite*>& ordreDAction) {
	std::sort(ordreDAction.begin(), ordreDAction.end(), Entite::comparerVitesse);
}
void Fight::lancerCombat() {
	// afficher ennemis
	std::deque<Entite*> ordreDAction;
	ordreDAction.push_back(joueur);
	for (Monstre *p : ennemis) {
		ordreDAction.push_back(p);
	}

	majOrdreDAction(ordreDAction);
	std::deque<ActionPerforme> actionPerforme;
	while (!isFinished()) {
		// 1.choix des action
		for (Entite* entite : ordreDAction) {
			//la struct ActionPerforme sera renvoyé par une fonction d'obtension
			ActionPerforme choixActuel;
			choixActuel.action = entite->getCompetence(0);
			choixActuel.cibles = std::vector<Entite*>{ ennemis.at(0) };
			// si la competence est prioritaire alors on .push_front()
			actionPerforme.push_back(choixActuel);
		}
		// 4.effectuer les actions dans l'ordre
		for (ActionPerforme actionActuel : actionPerforme) {
			//amélioré la robustesse ex(traiter les morts)
			actionActuel.action->utiliser(actionActuel.cibles);
		}
		std::cout << "tour finis";
		// 5.réordonner l'ordre d'action
	}
}
//ennemis.erase(std::remove_if(ennemis.begin(), ennemis.end(), [](Monstre m) {return !m.estVivant(); }), ennemis.end());