#include "DungeonGenerator.h"
#include<stack>
#include"Utilitaire.h"

IStateSalle* DungeonGenerator::possibleState[] = { new FightRoom,new EmptyRoom };
std::function<void(Position&, Salle*)> DungeonGenerator::constructConnections[] = {
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_NORTH), p.i--; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_SOUTH); p.i++; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_WEST), p.j--; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_EAST); p.j++; }
};
void completeConnexion(Position lastPos, Position currentPos, Donjon& dungeon) {
	//if lastPos.i == currentPos.i faire une des 2 pair
	//if lastPos.j == currentPos.j faire faire l'autre
	if (lastPos.j != currentPos.j) {
		if (dungeon.getRoom(currentPos.i, currentPos.j)->hasEastConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_WEST);
		}
		if (dungeon.getRoom(currentPos.i, currentPos.j)->hasWestConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_EAST);
		}
	}
	if (lastPos.i != currentPos.i) {
		if (dungeon.getRoom(currentPos.i, currentPos.j)->hasNorthConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_SOUTH);
		}
		if (dungeon.getRoom(currentPos.i, currentPos.j)->hasSouthConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_NORTH);
		}
	}
}

Donjon* DungeonGenerator::generateDonjon(Perso* player) {
	//générer la base du donjon
	int colSize = Utilitaire::getGeneratedInteger(tailleMinCol, tailleMaxCol);
	int lineSize = Utilitaire::getGeneratedInteger(tailleMinLine, tailleMaxLine);
	Donjon* donjon = new Donjon(player,colSize,lineSize);

	//placer le début
	int entranceY = Utilitaire::getGeneratedInteger(0, colSize - 1);
	int entranceX = Utilitaire::getGeneratedInteger(0, lineSize - 1);
	donjon->setCurrentX(entranceX);
	donjon->setCurrentY(entranceY);
	donjon->getRoom(entranceY, entranceX)->setIStateSalle(new CurrentRoom);

	//placer l'exit
	std::vector<Position> possibleExit;
	//possibleExit.reserve();
	for (int i{ 0 }; i < colSize; i++) {
		for (int j{ 0 }; j < lineSize; j++) {
			int distance = std::abs(i - entranceY) + std::abs(j - entranceX);
			if(distance>distanceMinToExit && distance<distanceMaxToExit){
				//donjon->getRoom(i, j)->setIStateSalle(new FightRoom); //indic toutes les sorties possibles
				Position pos{ i,j };
				possibleExit.push_back(pos);
			}
		}
	}
	Position posExit = possibleExit[Utilitaire::getGeneratedInteger(0, (int)possibleExit.size() - 1)];
	donjon->setExitX(posExit.j);
	donjon->setExitY(posExit.i);
	donjon->getRoom(posExit.i, posExit.j)->setIStateSalle(new StairsRoom);

	//faire le couloir entre depart et arrive
	std::stack<Position> roomParcour;
	Position posActuel{ entranceY,entranceX };
	roomParcour.push(posActuel);
	std::function<void(Position&, Salle*)> modifY = (posExit.i > posActuel.i ?  constructConnections[Direction::SOUTH] : constructConnections[Direction::NORTH]);
	std::function<void(Position&, Salle*)> modifX = (posExit.j > posActuel.j ? constructConnections[Direction::EAST] : constructConnections[Direction::WEST]);
	while (posExit.j != posActuel.j || posExit.i != posActuel.i) {
		bool aBouger = false;
		if (posExit.j != posActuel.j && Utilitaire::getGeneratedInteger(0,1) == 1) {
			modifX(posActuel,donjon->getRoom(posActuel.i,posActuel.j));
			aBouger = true;
		}
		if (posExit.i != posActuel.i && !aBouger) {
			modifY(posActuel, donjon->getRoom(posActuel.i, posActuel.j));
		}
		Salle* scs = donjon->getRoom(posActuel.i, posActuel.j);

		//Affiche le chemin vers la sortie
		/*if (scs->toString().compare("Stairs\n")) {
			scs->setIStateSalle(new FightRoom);
		}*/
		roomParcour.push(posActuel);
	}

	//dépiler
	while (!roomParcour.empty()) {
		Position posPrecedent = roomParcour.top();
		roomParcour.pop();
		
		if (!roomParcour.empty()) {
			posActuel = roomParcour.top();
			if (posActuel.i != donjon->getCurrentY() && posActuel.j != donjon->getCurrentX()) {
				//donjon->getRoom(posActuel.i, posActuel.j)->setIStateSalle(possibleState[Utilitaire::getGeneratedInteger(0, NB_STATE_POSSIBLE - 1)]);
			}
			completeConnexion(posPrecedent, posActuel, *donjon);

			//creer des sous couloirs à partir de la salle actuel
			//int sizeBaseStackRoom = (int)roomParcour.size();
			//int connectionRate = baseConnectionRate;
			//std::vector<Position> secondaryRoomParcour;
			//secondaryRoomParcour.push_back(roomParcour.top());
			//while(secondaryRoomParcour.size()>0) {
			//	Position secondaryCurrentPos = secondaryRoomParcour.back();
			//	if(connectionRate>Utilitaire::getGeneratedInteger(0,100)){
			//		Position newPosition = secondaryCurrentPos;
			//		connectionRate -= connectionRateVariation;
			//		
			//		int connection = Utilitaire::getGeneratedInteger(0, 3);
			//		constructConnections[connection](newPosition, donjon->getRoom(newPosition.i, newPosition.j));
			//		if (donjon->isValidRoom(newPosition.i, newPosition.j)) {
			//			secondaryRoomParcour.push_back(newPosition);
			//			//Affichage::afficher("connection en "+std::to_string(secondaryCurrentPos.i)+" "+std::to_string(secondaryCurrentPos.j)+"\n");
			//		}
			//	}
			//	else {
			//		connectionRate += connectionRateVariation;
			//		donjon->getRoom(secondaryCurrentPos.i, secondaryCurrentPos.j)->setIStateSalle(new FightRoom); //indic les salles et sous salle reliée
			//		Affichage::afficher("connection en " + std::to_string(secondaryCurrentPos.i) + " " + std::to_string(secondaryCurrentPos.j) + "\n");
			//		secondaryRoomParcour.pop_back();
			//		if (!secondaryRoomParcour.empty()) {
			//			completeConnexion(secondaryCurrentPos, secondaryRoomParcour.back(), *donjon);
			//		}
			//	}
			//}
		}
	}

	return donjon;
}