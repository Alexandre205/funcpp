#pragma once
#include"Salle.h"
class Donjon
{
private:
	//int floorNumber;
	int colSize; //y
	int lineSize; //x

	//matrice representing the actual floor
	//An array of array of pointers to a room
	Salle*** floor; 
public:
	std::string toString();
	Donjon(int lineSize, int colSize);
	int getColSize();
	int getLineSize();
	void initFloor();
	
};