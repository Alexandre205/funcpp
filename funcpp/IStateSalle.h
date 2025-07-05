#pragma once
#include"Perso.h"
class IStateSalle
{
public:
	virtual void passage(Perso& joueur) = 0;
};

//This room is unaccessible unless error
class WallRoom : public IStateSalle{
public:
	void passage(Perso& joueur);
};

//This room is empty
class EmptyRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};

//This room contain a fight against monster
class FightRoom : public IStateSalle {
public:
	//FightRoom(Liste Monstre);
	void passage(Perso& joueur);
};

//This room is where the player is currently in
class CurrentRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};

//This room make games end
class StairsRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};

//This room contain a chess to open
class ChestRoom : public IStateSalle {
public:
	Consommable* tresor;
	ChestRoom();
	void passage(Perso& joueur);
};

//This room has a merchant in it to buy him goods and items
class MerchantRoom : public IStateSalle {
public :
	//MerchantRoom(Liste item);
	void passage(Perso& joueur);
};