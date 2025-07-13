#pragma once
#include"Perso.h"
class IStateSalle
{
public:
	//bool is use to know if the room must be emptied
	virtual bool passage(Perso& joueur) = 0;
};

//This room is unaccessible unless error
class WallRoom : public IStateSalle{
public:
	bool passage(Perso& joueur);
};

//This room is empty
class EmptyRoom : public IStateSalle {
public:
	bool passage(Perso& joueur);
};

//This room contain a fight against monster
class FightRoom : public IStateSalle {
	std::vector<Monstre> ennemis;
public:
	FightRoom();
	bool passage(Perso& joueur);
};

//This room is where the player is currently in
class CurrentRoom : public IStateSalle {
public:
	bool passage(Perso& joueur);
};

//This room make games end
class StairsRoom : public IStateSalle {
public:
	bool passage(Perso& joueur);
};

//This room contain a chess to open
class ChestRoom : public IStateSalle {
private:
	Consommable tresor;
public:
	ChestRoom();
	bool passage(Perso& joueur);
};

//This room has a merchant in it to buy him goods and items
class MerchantRoom : public IStateSalle {
private :
	std::vector<Consommable> listeItem;
public :
	MerchantRoom();
	bool passage(Perso& joueur);
};