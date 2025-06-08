#pragma once
#include"Entite.h"
namespace Effets
{
	void soinPv(Entite& cible,int puissance);
	void soinPm(Entite& cible,int puissance);
	void soinPvEtPm(Entite& cible, int puissance);
	void infligerDegat(Entite& cible, int puissance);
};