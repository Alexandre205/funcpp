#pragma once
#include"Entite.h"
class EffetsConsommable
{

public:
	static void soinPv(Entite& cible,int puissance);
	static void soinPm(Entite& cible,int puissance);
	static void soinPvEtPm(Entite& cible, int puissance);
	static void resucitePlusSoin(Entite& cible, int puissance);
};