#pragma once
#include<functional>
#include<map>
#include"Donjon.h"
struct Position {
	int i, j;
	bool operator<(const Position& other) const;
};

class DungeonGenerator
{
private:
	static const int NB_STATE_POSSIBLE = 2;
	static IStateSalle* possibleState[NB_STATE_POSSIBLE];

	//array to use to move and construct the room of the donjon
	static std::function<void(Position&,Salle*)> constructConnections[4];
	static std::map<Position, int> nbVisitRoom;

	static const int tailleMaxLine = 7;
	static const int tailleMaxCol = 7;
	static const int tailleMinLine = 4;
	static const int tailleMinCol = 4;
	static const int distanceMinToExit = 3; // Si je dois augmenter ca alors il faut augmenter la taille min des donjon
	static const int distanceMaxToExit = 9;
	static const int baseConnectionRate = 70; //sur 100, chance de base d'avoir une connection 
	static const int connectionRateVariation = 10; //diminution des chances d'avoir une connection a chaque enfoncement

	static void creerSousCouloir(Position depart, Donjon& donjon, int profondeurMax);
public:
	//Donjon* generateDonjon();
	//Donjon* generateDonjon(/*Parametre de generation*/);
	//Donjon* generateDonjon(/*seed*/);
	static Donjon* generateDonjon(Perso* player);
};