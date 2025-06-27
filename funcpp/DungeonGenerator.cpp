#include "DungeonGenerator.h"
#include<stack>
#include"Utilitaire.h"

IStateSalle* DungeonGenerator::possibleState[] = { new FightRoom,new EmptyRoom };
std::function<void(Position&, Salle*)> DungeonGenerator::constructConnections[] = {
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_NORTH); p.i--; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_SOUTH); p.i++; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_WEST); p.j--; },
	[](Position& p, Salle* s) {s->addConnexion(Connexion::CONNEXION_EAST); p.j++; }
};
std::map<Position, int> DungeonGenerator::nbVisitRoom;
bool Position::operator<(const Position& other) const {
	return (i < other.i) || (i == other.i && j < other.j);
}
void completeConnexion(Position lastPos, Position currentPos, Donjon& dungeon) {
	if (lastPos.j != currentPos.j) {
		if (lastPos.j > currentPos.j && dungeon.getRoom(currentPos.i, currentPos.j)->hasEastConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_WEST);
		}
		if (lastPos.j < currentPos.j && dungeon.getRoom(currentPos.i, currentPos.j)->hasWestConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_EAST);
		}
	}
	if (lastPos.i != currentPos.i) {
		if (lastPos.i < currentPos.i && dungeon.getRoom(currentPos.i, currentPos.j)->hasNorthConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_SOUTH);
		}
		if (lastPos.i > currentPos.i && dungeon.getRoom(currentPos.i, currentPos.j)->hasSouthConnexion()) {
			dungeon.getRoom(lastPos.i, lastPos.j)->addConnexion(Connexion::CONNEXION_NORTH);
		}
	}
}
void DungeonGenerator::creerSousCouloir(Position pos, Donjon& donjon, int connectionRate) {
	//ici passe toutes les salles des sous couloirs
	if (donjon.getRoom(pos.i, pos.j)->toString() == "Wall\n") {
		donjon.getRoom(pos.i, pos.j)->setIStateSalle(SalleType::Empty);
	}
	if (donjon.getRoom(pos.i, pos.j)->toString() != "Stairs\n" && connectionRate > Utilitaire::getGeneratedInteger(1,100)) {
		std::vector<Position> voisinsPossibles;
		std::vector<Connexion> connexionPossibles;
		if (pos.i > 0 && nbVisitRoom[{pos.i - 1, pos.j}] == 0) {
			voisinsPossibles.push_back({ pos.i - 1, pos.j });
			connexionPossibles.push_back(Connexion::CONNEXION_SOUTH);
		}
		if (pos.i < donjon.getColSize() - 1 && nbVisitRoom[{pos.i + 1, pos.j}] == 0) {
			voisinsPossibles.push_back({ pos.i + 1, pos.j });
			connexionPossibles.push_back(Connexion::CONNEXION_NORTH);
		}
		if (pos.j > 0 && nbVisitRoom[{pos.i, pos.j - 1}] == 0) {
			voisinsPossibles.push_back({ pos.i, pos.j - 1 });
			connexionPossibles.push_back(Connexion::CONNEXION_EAST);
		}
		if (pos.j < donjon.getLineSize() - 1 && nbVisitRoom[{pos.i, pos.j + 1}] == 0) {
			voisinsPossibles.push_back({ pos.i, pos.j + 1 });
			connexionPossibles.push_back(Connexion::CONNEXION_WEST);
		}
		if (!voisinsPossibles.empty()) {
			int i = Utilitaire::getGeneratedInteger(0, (int)voisinsPossibles.size() - 1);
			Position newPos = voisinsPossibles[i];
			donjon.getRoom(newPos.i, newPos.j)->addConnexion(connexionPossibles[i]);
			nbVisitRoom[newPos]++;
			creerSousCouloir(newPos, donjon, connectionRate - connectionRateVariation);
			completeConnexion(pos, newPos, donjon);
		}
		
	}else {
		//ici ne passera que la derniere salle du sous couloir
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
	donjon->getRoom(entranceY, entranceX)->setIStateSalle(SalleType::Current);
	
	//placer l'exit
	std::vector<Position> possibleExit;
	//possibleExit.reserve();
	for (int i{ 0 }; i < colSize; i++) {
		for (int j{ 0 }; j < lineSize; j++) {
			int distance = std::abs(i - entranceY) + std::abs(j - entranceX);
			if(distance>distanceMinToExit && distance<distanceMaxToExit){
				//donjon->getRoom(i, j)->setIStateSalle(SalleType::Battle); //indic toutes les sorties possibles
				Position pos{ i,j };
				possibleExit.push_back(pos);
			}
		}
	}
	Position posExit = possibleExit[Utilitaire::getGeneratedInteger(0, (int)possibleExit.size() - 1)];
	donjon->setExitX(posExit.j);
	donjon->setExitY(posExit.i);
	donjon->getRoom(posExit.i, posExit.j)->setIStateSalle(SalleType::Stairs);
	possibleExit.clear();
	possibleExit.shrink_to_fit();

	//faire le couloir entre depart et arrive
	std::stack<Position> roomParcour;
	Position posActuel{ entranceY,entranceX };
	roomParcour.push(posActuel);
	std::function<void(Position&, Salle*)> modifY = (posExit.i > posActuel.i ?  constructConnections[Direction::SOUTH] : constructConnections[Direction::NORTH]);
	std::function<void(Position&, Salle*)> modifX = (posExit.j > posActuel.j ? constructConnections[Direction::EAST] : constructConnections[Direction::WEST]);
	while (posExit.j != posActuel.j || posExit.i != posActuel.i) {
		//a changer pour eviter les passages sans bouger
		bool aBouger = false;
		if (posExit.j != posActuel.j && Utilitaire::getGeneratedInteger(0,1) == 1) {
			modifX(posActuel,donjon->getRoom(posActuel.i,posActuel.j));
			aBouger = true;
		}
		if (posExit.i != posActuel.i && !aBouger) {
			modifY(posActuel, donjon->getRoom(posActuel.i, posActuel.j));
		}
		Salle* scs = donjon->getRoom(posActuel.i, posActuel.j);
		roomParcour.push(posActuel);
	}

	//dépiler
	Position posPrecedent = roomParcour.top();
	roomParcour.pop();
	while (!roomParcour.empty()) {
		posActuel = roomParcour.top();		

		//creer des sous couloirs à partir de la salle actuel
		creerSousCouloir(posActuel, *donjon, baseConnectionRate);
		completeConnexion(posPrecedent, posActuel, *donjon);
		posPrecedent = posActuel;
		roomParcour.pop();
	}
	
	nbVisitRoom.clear();
	return donjon;
}