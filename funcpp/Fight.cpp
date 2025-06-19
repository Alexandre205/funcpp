#include<algorithm>
#include<list>

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

//implementation à changer pour retourner la raison de l'arret //et faire le booléen correctment
bool Fight::isFinished() {
	if (!joueur->estVivant()) {
		return true;
	}
	return ennemis.size() == 0;
}
void Fight::majOrdreDAction(std::deque<Entite*>& ordreDAction) {
	//Peut-etre faire un buble sort pour car c'est une list peu désordonné
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

	std::list<ActionPerforme> actionPerforme;
	while (!isFinished()) {
		// 1.choix des action
		for (Entite* entite : ordreDAction) {
			ActionPerforme choixActuel = entite->getAction(*this->joueur,ennemis);
			int priorite = choixActuel.action->getPriority();

			//actionPerforme doit etre trie sur la priorité puis par rapport à l'ordre de leur ajout
			std::list<ActionPerforme>::iterator it = actionPerforme.begin();
			while (it != actionPerforme.end() && priorite <= it->action->getPriority()) {
				it++;
			}
			actionPerforme.insert(it, choixActuel);
		}
		// 2.effectuer les actions dans l'ordre
		for (ActionPerforme actionActuel : actionPerforme) {
			if (!actionActuel.lanceur->estVivant()) {
				Affichage::afficher(actionActuel.lanceur->getNom() + " est mort. Impossible de lancer son attaque\n");
			}
			else {
				//si il y a un bug en rapport avec le droit d'utilisation d'une competence creuse ici
				int i = 0;
				while (i < actionActuel.cibles.size() && !actionActuel.cibles[i]->estVivant()) {
					i++;
				}
				if (i == actionActuel.cibles.size()) {
					Affichage::afficher("La cible selectionee n'est pas valable pour faire l'action de "+actionActuel.lanceur->getNom()+"\n");
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