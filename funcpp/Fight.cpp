#include<algorithm>

#include"Fight.h"
#include"Utilitaire.h"
#include"IUsable.h"

std::string Fight::toSring() {
	return listeMonstrePresent();
}

Fight::Fight(Perso* joueur, std::vector<Monstre*> ennemis) :joueur{ joueur } {
	int i = 0;
	while (i < NB_MONSTRE_MAX && i<ennemis.size()) {
		addEnnemis(ennemis[i]);
		i++;
	}
}

void Fight::addEnnemis(Monstre* ennemi) {
	if (ennemis.size() < NB_MONSTRE_MAX) {
		ennemis.push_back(ennemi);
	}
	else {
		Utilitaire::writeInLog("Plus d'espace pour faire apparaitre un nouveau monstre");
	}
}

std::string Fight::listeMonstrePresent() {
	std::string liste = "";
	for (int i = 0; i < ennemis.size(); i++) {
		liste += std::to_string(i+1) + "." + ennemis[i]->getNom() + "\n";
	}
	return liste;
}

//implementation à changer pour retourner la raison de l'arret
bool Fight::isFinished() {
	if (!joueur->estVivant()) {
		return true;
	}
	return ennemis.size() == 0;
}
void Fight::majOrdreDAction(std::deque<Entite*>& ordreDAction) {
	if (!std::is_sorted(ordreDAction.begin(), ordreDAction.end(), Entite::comparerVitesse)) {
		std::sort(ordreDAction.begin(), ordreDAction.end(), Entite::comparerVitesse);
	}
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
			//ActionPerforme ap = obtenirAction //peut-etre lier à l'entite avec du poly
			ActionPerforme choixActuel;
			choixActuel.action = entite->getCompetence(0); //test
			choixActuel.cibles = std::vector<Entite*>{ ennemis.at(0) };//test
			choixActuel.lanceur = entite;
			// si la competence est prioritaire alors on .push_front() // mais pas que
			actionPerforme.push_back(choixActuel);
		}
		// 2.effectuer les actions dans l'ordre
		for (ActionPerforme actionActuel : actionPerforme) {
			if (!actionActuel.lanceur->estVivant()) {
				Affichage::afficher(actionActuel.lanceur->getNom() + " est mort. Impossible de lancer l'attaque\n");
			}
			else {
				int i = 0;
				while (i < actionActuel.cibles.size() && !actionActuel.cibles[i]->estVivant()) {
					i++;
				}
				if (i == actionActuel.cibles.size()) {
					Affichage::afficher("Aucune cible valable pour faire l'action de "+actionActuel.lanceur->getNom()+"\n");
				}
				else {
					actionActuel.action->utiliser(actionActuel.cibles);
				}
			}
		}
		//3.remettre en ordre
		ennemis.erase(std::remove_if(ennemis.begin(), ennemis.end(), [](Monstre *m) {return !m->estVivant(); }), ennemis.end());
		ordreDAction.erase(std::remove_if(ordreDAction.begin(), ordreDAction.end(), [](Entite* e) {return !e->estVivant(); }), ordreDAction.end());
		majOrdreDAction(ordreDAction);
		actionPerforme.clear();
	}
}