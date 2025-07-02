#pragma once
#include<functional>
#include<vector>
#include<string>

class Entite;
enum Ciblage;
class ICiblage {
public:
	static Ciblage intToICiblage(int i);
	virtual std::vector<Entite*> selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie) = 0;
};

class MonoCible : public ICiblage {
public:
	std::vector<Entite*> selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie);
};

class MultiCible : public ICiblage {
public:
	std::vector<Entite*> selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie);
};

class SelfCible : public ICiblage {
public:
	std::vector<Entite*> selectionnerCible(std::vector<Entite*>& ennemis, std::vector<Entite*>& allie);
};

