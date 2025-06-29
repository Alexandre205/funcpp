#pragma once
#include<functional>
#include<map>
#include"Donjon.h"
struct Position {
	int i, j;

	//use to make it a std::map
	bool operator<(const Position& other) const;
};

class DungeonGenerator
{
private:
	

	//array to use to move and construct the room of the donjon
	static std::function<void(Position&,Salle*)> constructConnections[4];
	static std::map<Position, int> nbVisitRoom;


	//parameters for the dungeon generation

	//Size parameters
	static const int tailleMaxLine = 7;
	static const int tailleMaxCol = 7;
	static const int tailleMinLine = 4;
	static const int tailleMinCol = 4;
	static const int distanceMinToExit = 3; // Si je dois augmenter ca alors il faut augmenter la taille min des donjon
	static const int distanceMaxToExit = 9;

	//connexion rate
	static const int baseConnectionRate = 70; //sur 100, chance de base d'avoir une connection 
	static const int connectionRateVariation = 10; //diminution des chances d'avoir une connection a chaque enfoncement
	
	//Content rate
	static const int nbChestMaxInDungeon = 3;
	static const int chestApparitionRate = 40; //les coffres n'apparaissent que en fin de sous-couloir
	static int nbChestInDungeon;
	static const int figthApparitionRate = 45;
	static const int nbMerchantMaxInDungeon = 1; 
	static const int merchantApparitionRate = 15; //les marchand n'apparaissent qu'en fin de couloir
	static int nbMerchantInDungeon;

	//Called while depiling to link the 2 rooms togethers
	static void completeConnexion(Position lastPos, Position currentPos, Donjon& dungeon);

	//Recursive fonction to create secondary path on the main one
	static void creerSousCouloir(Position depart, Donjon& donjon, int profondeurMax);
public:

	//Generate a dungeon based on the initailited seed
	static Donjon* generateDonjon(Perso* player);
};