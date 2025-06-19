#include "Donjon.h"
#include"Utilitaire.h"

std::string Donjon::toString() {
	std::string s;
	s.append(std::to_string(lineSize) + ' ' + std::to_string(colSize) + '\n');
	for (int j{ 0 }; j < lineSize; j++) {
		s.append("----");
	}
	s.append("-\n");
	for (int i{ 0 }; i < colSize; i++) {
		s.append("| ");
		for (int j{ 0 }; j < lineSize; j++) {
			s.append(floor[i][j]->getContent() + " | ");
		}
		s.append("\n");
		for (int j{ 0 }; j < lineSize; j++) {
			s.append("----");
		}
		s.append("-\n");
	}
	return s;
}

Donjon::Donjon(int colSize,int lineSize) {
	this->colSize = colSize;
	this->lineSize = lineSize;
	initFloor();
}

void Donjon::initFloor() {
	floor = new Salle**[colSize];
	Utilitaire::testHandler(floor != NULL, "Plus d'espace mémoire", false);
	for (int i{ 0 }; i < colSize; i++) {
		floor[i] = new Salle*[lineSize];
		Utilitaire::testHandler(floor[i] != NULL, "Plus d'espace mémoire", false);
		for (int j{ 0 }; j < lineSize; j++) {
			floor[i][j] = new Salle{new FightRoom};
			Utilitaire::testHandler(floor[i][j] != NULL, "Plus d'espace mémoire", false);
		}
	}
}
int Donjon::getColSize() {
	return colSize;
}
int Donjon::getLineSize() {
	return lineSize;
}