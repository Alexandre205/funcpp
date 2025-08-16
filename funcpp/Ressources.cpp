#include "Ressources.h"

DataEquipment Ressources::dataEquipment;
std::vector<Monstre> Ressources::dataMonsters;
std::vector<Consommable> Ressources::dataConsommable;
std::map<int, std::vector<Competence>> Ressources::dataPlayerComp;
void Ressources::initRessources() {
    Ressources::dataEquipment = FileManagement::getEquipmentFromFile();
    Ressources::dataConsommable = FileManagement::getConsumablesFromFile();
    Ressources::dataMonsters = FileManagement::getMonstersFromFile();
    Ressources::dataPlayerComp = FileManagement::getPlayerCompFromFile();
}