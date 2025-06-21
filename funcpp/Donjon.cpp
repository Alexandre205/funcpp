#include "Donjon.h"
#include "Utilitaire.h"
#include "InputConsole.h"

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

Donjon::Donjon(Perso* player,int colSize,int lineSize,int currentY,int currentX) {
	this->player = player;
	this->colSize = colSize;
	this->lineSize = lineSize;
	setCurrentX(currentX);
	setCurrentY(currentY);
	initFloor();
}

void Donjon::initFloor() {
	floor = new Salle**[colSize];
	Utilitaire::testHandler(floor != NULL, "Plus d'espace mémoire");
	for (int i{ 0 }; i < colSize; i++) {
		floor[i] = new Salle*[lineSize];
		Utilitaire::testHandler(floor[i] != NULL, "Plus d'espace mémoire");
		for (int j{ 0 }; j < lineSize; j++) {
			floor[i][j] = new Salle{new EmptyRoom,Connexion::CONNEXION_ALL};
			Utilitaire::testHandler(floor[i][j] != NULL, "Plus d'espace mémoire");
		}
	}
	for (int i{ 0 }; i < lineSize; i++) {
		floor[0][i]->removeConnexion(Connexion::CONNEXION_NORTH);
		floor[colSize - 1][i]->removeConnexion(Connexion::CONNEXION_SOUTH);
	}
	for (int i{ 0 }; i < colSize; i++) {
		floor[i][0]->removeConnexion(Connexion::CONNEXION_WEST);
		floor[i][lineSize-1]->removeConnexion(Connexion::CONNEXION_EAST);
	}
	floor[currentY][currentX]->setIStateSalle(new CurrentRoom);
}

void Donjon::move() {
	Direction direction = Obtention::getDirection(floor[currentY][currentX]);//choose a direction
	floor[currentY][currentX]->setIStateSalle(new EmptyRoom);//Change the last room state to EmptyRoom
	switch (direction) {
		case NORTH:currentY--; break;
		case SOUTH:currentY++; break;
		case WEST:currentX--; break;
		case EAST:currentX++; break;
		default:Utilitaire::unexpectedExit("Probleme avec les directions");
	}
	floor[currentY][currentX]->passage(*player);//move to the new room//Salle->passage();
	floor[currentY][currentX]->setIStateSalle(new CurrentRoom);//change the state of the room to CurrentRoom
}

void Donjon::setCurrentX(int currentX) {
	Utilitaire::testHandler(currentX >= 0 && currentX < lineSize, "Indice hors porté du donjon");
	this->currentX = currentX;
}
void Donjon::setCurrentY(int currentY) {
	Utilitaire::testHandler(currentY>=0 && currentY<colSize, "Indice hors porté du donjon");
	this->currentY = currentY;
}
int Donjon::getCurrentX() { 
	return currentX; 
}
int Donjon::getCurrentY() { 
	return currentY; 
}
Salle* Donjon::getRoom(int i, int j) {
	Utilitaire::testHandler(i>=0 && i<colSize && j>=0 && j<lineSize,"Indice hors porté du donjon");
	return floor[i][j];
}
int Donjon::getColSize() {
	return colSize;
}
int Donjon::getLineSize() {
	return lineSize;
}