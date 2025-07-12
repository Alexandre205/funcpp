#pragma once
#include"ILootable.h"
#include<string>

class Equipment : public ILootable
{
private:
	std::string nom;
	std::string description;
public:
	std::string toString();
	Equipment(std::string nom, std::string description);
	std::string getNom();
	std::string getDescription();
};