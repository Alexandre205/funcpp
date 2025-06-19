#pragma once
#include"Perso.h"
class IStateSalle
{
public:
	virtual void passage(Perso& joueur) = 0;
};
class Wall : public IStateSalle{
public:
	void passage(Perso& joueur);
};
class EmptyRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};
class FightRoom : public IStateSalle {
public:
	void passage(Perso& joueur);
};