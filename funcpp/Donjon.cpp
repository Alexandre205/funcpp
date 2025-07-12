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
			s.append(floor[i][j]->getContentString() + " | ");
		}
		s.append("\n");
		for (int j{ 0 }; j < lineSize; j++) {
			s.append("----");
		}
		s.append("-\n");
	}
	return s;
}

Donjon::Donjon(Perso* player,int colSize,int lineSize) {
	this->player = player;
	this->colSize = colSize;
	this->lineSize = lineSize;
	initFloor();
}

void Donjon::initFloor() {
	floor = new Salle**[colSize];
	Utilitaire::testHandler(floor != NULL, "Plus d'espace mémoire");
	for (int i{ 0 }; i < colSize; i++) {
		floor[i] = new Salle*[lineSize];
		Utilitaire::testHandler(floor[i] != NULL, "Plus d'espace mémoire");
		for (int j{ 0 }; j < lineSize; j++) {
			floor[i][j] = new Salle{ SalleType::Wall,Connexion::CONNEXION_NONE};
			Utilitaire::testHandler(floor[i][j] != NULL, "Plus d'espace mémoire");
		}
	}
}

void Donjon::move() {
	Direction direction = Obtention::getDirection(floor[currentY][currentX]);//choose a direction
	floor[currentY][currentX]->setIStateSalle(SalleType::Empty);//Change the last room state to EmptyRoom
	switch (direction) {
		case NORTH:currentY--; break;
		case SOUTH:currentY++; break;
		case WEST:currentX--; break;
		case EAST:currentX++; break;
		default:Utilitaire::unexpectedExit("Probleme avec les directions");
	}
	Affichage::clear();
	floor[currentY][currentX]->passage(*player);//move to the new room//Salle->passage();

	//à changer pour gérer les different state
	floor[currentY][currentX]->setIStateSalle(SalleType::Current);//change the state of the room to CurrentRoom
}
void Donjon::explore() {
	Affichage::afficher("Vous penetrez dans le donjon.\n");
	//Mettre a jour la boucle pour pouvoir perdre
	while ((currentX != exitX || currentY != exitY) && player->estVivant() ) {
		Affichage::displayDonjon(*this);
		move();
	}
	if (player->estVivant()) {
		Affichage::afficher("bravo vous avez survecu\n");
	}
	else {
		Affichage::afficher("Vous avez ete bouffer par le donjon\n");
	}
}

void Donjon::setCurrentX(int currentX) {
	Utilitaire::testHandler(currentX >= 0 && currentX < lineSize, "Indice hors porté du donjon");
	this->currentX = currentX;
}
void Donjon::setCurrentY(int currentY) {
	Utilitaire::testHandler(currentY>=0 && currentY<colSize, "Indice hors porté du donjon");
	this->currentY = currentY;
}
void Donjon::setExitX(int exitX) {
	Utilitaire::testHandler(exitX >= 0 && exitX < lineSize, "Indice hors porté du donjon");
	this->exitX = exitX;
}
void Donjon::setExitY(int exitY) {
	Utilitaire::testHandler(exitY >= 0 && exitY < colSize, "Indice hors porté du donjon");
	this->exitY = exitY;
}
int Donjon::getCurrentX() { 
	return currentX; 
}
int Donjon::getCurrentY() { 
	return currentY; 
}
int Donjon::getExitX() {
	return exitX;
}
int Donjon::getExitY() {
	return exitY;
}
Salle* Donjon::getRoom(int i, int j) {
	Utilitaire::testHandler(i>=0 && i<colSize && j>=0 && j<lineSize,"Indice hors porté du donjon");
	return floor[i][j];
}
bool Donjon::isValidRoom(int i, int j) {
	return i >= 0 && i < colSize && j >= 0 && j < lineSize;
}
int Donjon::getColSize() {
	return colSize;
}
int Donjon::getLineSize() {
	return lineSize;
}