#pragma once
#include"Perso.h"
class IStateSalle
{
public:
	virtual void passage(Perso& joueur) = 0;
};

//This room is unaccessible unless error
class Wall : public IStateSalle{
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
	void passage(Perso& joueur);
};

//This room is where the player is currently in
class CurrentRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};