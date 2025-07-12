#include "Ressources.h"

DataEquipment Ressources::dataEquipment;
std::vector<Monstre> Ressources::dataMonsters;
std::vector<Consommable> Ressources::dataConsommable;
void Ressources::initRessources() {
    Ressources::dataEquipment = FileManagement::getEquipmentFromFile();
    Ressources::dataConsommable = FileManagement::getConsumablesFromFile();
    Ressources::dataMonsters = FileManagement::getMonstersFromFile();
}