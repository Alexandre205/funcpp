#include<algorithm>
#include<list>

#include"Fight.h"
#include"Utilitaire.h"
#include"IUsable.h"

std::string Fight::toSring() {
	return listeMonstrePresent();
}

Fight::Fight(Perso* joueur, std::vector<Monstre>& ennemis) : joueur{ joueur } {
	int i = 0;
	while (i < NB_MONSTRE_MAX && i<ennemis.size()) {
		addEnnemis(ennemis[i]);
		i++;
	}
}

void Fight::addEnnemis(Monstre ennemi) {
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
		liste += std::to_string(i+1) + "." + ennemis[i].getNom() + "\n";
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
	//Peut-etre faire un buble sort pour car c'est une list peu désordonnée
	if (!std::is_sorted(ordreDAction.begin(), ordreDAction.end(), Entite::comparerVitesse)) {
		std::sort(ordreDAction.begin(), ordreDAction.end(), Entite::comparerVitesse);
	}
}
void Fight::lancerCombat() {
	// afficher ennemis
	int recompense = 0;
	std::deque<Entite*> ordreDAction;
	ordreDAction.push_back(joueur);
	std::string s;
	for (Monstre& p : ennemis) {
		ordreDAction.push_back(&p);
		recompense += p.goldLache();
		s.append(p.toString() + "\n");
	}
	s.append("Que faites vous ?\n");
	Affichage::afficher(s);

	majOrdreDAction(ordreDAction);

	std::list<ActionPerforme> actionPerforme;
	bool endOfFight = false;
	while (!endOfFight) {
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
			if(actionActuel.lanceur->estVivant()) {
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
					for (Entite* ent : actionActuel.cibles) {
						if (!ent->estVivant()) {
							Affichage::afficher(ent->getNom() + " est mort\n");
						}
					}
				}
			}
		}

		//3.effacer les monstres mort 
		ennemis.erase(std::remove_if(ennemis.begin(), ennemis.end(), [](Monstre& m) {return !m.estVivant(); }), ennemis.end());
		ordreDAction.erase(std::remove_if(ordreDAction.begin(), ordreDAction.end(), [](Entite* e) {return !e->getNom().compare(""); }), ordreDAction.end()); //obligatoire pour éviter les pointeur vide

		
		endOfFight = isFinished();
		if (!endOfFight) {
			//4.remettre en ordre
			majOrdreDAction(ordreDAction);
			actionPerforme.clear();
			s.clear();
			for (Monstre& p : ennemis) {
				s.append(p.toString() + "\n");
			}
			s.append("Que faite vous ?\n");
			Affichage::afficher(s);
		}
	}
	//ajouter possiblement un petit lag le temps de pouvoir lire le texte
	Affichage::clear();
	//Afficher un truc different en fonction de si on a gagner ou pas
	if (joueur->estVivant()) {
		Affichage::afficher("Vous avez gagner le combat\nVous gagne "+std::to_string(recompense)+" golds\n");
		joueur->modifyNbGold(recompense);
	}
	else {
		Affichage::afficher("Vous etes mort\n");
	}
	
}