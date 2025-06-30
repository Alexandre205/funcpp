#pragma once
#include<array>

#include"Casque.h"
#include"Arme.h"
#include"Armure.h"
#include"Botte.h"
#include"Consommable.h"

class Inventaire
{
public:
	static const int TAILLE_DE_BASE_INVENTAIRE = 5;
private:
	Casque casque;
	Arme arme;
	Armure armure;
	Botte botte;
	std::array<Consommable*, TAILLE_DE_BASE_INVENTAIRE> inventaire;//non trié
	int nbConsommable;
	int tailleInventaire;
	// std::list<Consomable> extraInventaire
public:
	std::string toString();

	Inventaire();

	// il faudra faire quelque changement en presence d'un extra d'inventaire
	// pour le moment juste 1 inventaire limiter a 5
	void ajouterConsommable(Consommable& nouvConso);
	void supprimerConsommable(int indiceConso);

	void ajouterEquipement(Casque casque);
	void ajouterEquipement(Arme arme);
	void ajouterEquipement(Armure armure);
	void ajouterEquipement(Botte botte);

	Casque getCasque();
	Arme getArme();
	Armure getArmure();
	Botte getBotte();

	Consommable* getConsumable(int i);
	int getNbConsommable();
	std::string getConsumableList();
};