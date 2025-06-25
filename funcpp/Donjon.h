#pragma once
#include"Salle.h"
enum Direction {
	NORTH,SOUTH,WEST,EAST
};

class Donjon
{
private:
	Perso* player;
	//int floorNumber;
	int colSize; //y
	int lineSize; //x

	//Current position of the CurrentRoom
	int currentY;
	int currentX;
	
	//Position of the StairsRoom
	int exitY;
	int exitX;

	//matrice representing the actual floor
	//An array of array of pointers to a room
	Salle*** floor; 
public:
	std::string toString();
	Donjon(Perso* player,int lineSize, int colSize);
	//Donjon(Perso* player, int lineSize, int colSize);
	void initFloor();


	void move();

	Salle* getRoom(int i, int j);
	bool isValidRoom(int i, int j);
	void setCurrentX(int currentX);
	void setCurrentY(int currentY);
	void setExitX(int exitX);
	void setExitY(int exitY);
	int getCurrentX();
	int getCurrentY();
	int getExitX();
	int getExitY();
	int getColSize();
	int getLineSize();
};