#include "Ressources.h"

void Ressources::initRessources() {
	dataEquipment = FileManagement::getEquipmentFromFile();
	dataConsommable = FileManagement::getConsumablesFromFile();
	dataMonsters = FileManagement::getMonstersFromFile();
}