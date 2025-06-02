#pragma once
#include<functional>
#include<vector>
#include<string>

class Entite;
class Monstre;

class ICiblage {
public:
	virtual void appliquerEffet(std::function<void(Entite&, int)>effet, std::vector<Entite*>& cibles,Entite& lanceur,std::string formuleDegat) = 0;
	virtual std::vector<Entite*> selectionnerCible(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie) = 0;
};

class MonoCible : public ICiblage {
public:
	void appliquerEffet(std::function<void(Entite&, int)>effet, std::vector<Entite*>& cibles, Entite& lanceur, std::string formuleDegat);
	std::vector<Entite*> selectionnerCible(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie);
};

class MultiCible : public ICiblage {
public:
	void appliquerEffet(std::function<void(Entite&, int)>effet, std::vector<Entite*>& cibles, Entite& lanceur, std::string formuleDegat);
	std::vector<Entite*> selectionnerCible(std::vector<Monstre*>& ennemis, std::vector<Entite*>& allie);
};