#pragma once
#include<iostream>

#include"Entite.h"
#include"Item.h"
#include"Competence.h"
#include"Inventaire.h"
#include"Monstre.h"
#include"Perso.h"
#include"Fight.h"
#include"Donjon.h"
namespace Affichage
{
	void afficher(std::string st);
	void afficher(std::vector<Entite*>& ens);
	void afficher(Entite& en);
	void afficher(Item& it);
	void afficher(Competence& co);
	void afficher(Inventaire* in);
	void afficher(Inventaire& in);
	//void afficher(Monstre& mo);
	void afficher(Perso& pe);
	void afficher(Fight& fi);
	void afficher(Salle& sa);
	void afficher(Donjon& dj);
	void displayDonjon(Donjon& dj);
};