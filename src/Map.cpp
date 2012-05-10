/*
 * Map.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Map.h"

Map::Map() {
	//Construction de la map - codée à la dure
	this->width = 40;
	this->height = 60;

	this->map = new Cell**[this->width];

	//Initialisation
	for(int i=0 ; i < this->width ;i++) {
		this->map[i] = new Cell*[this->height];

		for(int j=0 ; j < this->height ;j++) {
			this->map[i][j] = new Cell(i, j, false);
		}
	}

	//Construction des zones
	//Capitaine gauche - X(de 0cm à 500mm (10 cases)) sur Y(1500mm à 2000mm (10cases))
	this->captainAreaLeft = new Area(this->getZone(0, 1500, 500, 500), this->getCellWithDistance(100, 1800), 100);

	//Câle gauche - X(de 0mm à 400mm (8 cases)) sur Y(750mm à 1500mm (15cases))
	this->stockAreaLeft = new Area(this->getZone(0, 750, 400, 750), this->getCellWithDistance(100, 1650), 120);

		//Capitaine droite - X(de 2500mm à 3000mm (10 cases)) sur Y(1500mm à 2000mm (10cases))
	this->captainAreaRight = new Area(this->getZone(2500, 1500, 500, 500), this->getCellWithDistance(2900, 1800), 100);

		//Câle droite - X(de 2600mm à 3000mm (8 cases)) sur Y(750mm à 1500mm (15cases))
	this->stockAreaRight = new Area(this->getZone(2600, 750, 400, 750), this->getCellWithDistance(2900, 1650), 120);


	//Régler les obstacles fixes
		//Câle avec couvercle : on n'y rentre pas !
		//Partie gauche
			// X(de 0mm à 400mm (4 cases)) sur Y(0cm à 750mm (7cases))
	this->setZoneBlocked(0, 0, 400, 750);
		//Partie droite
			// X(de 2600mm à 3000mm (4 cases)) sur Y(0mm à 750mm (7cases))
	this->setZoneBlocked(2600, 0, 400, 750);

		//Poteau gauche
			// X(de 975cm à 1225cm (25 cases+2)) sur Y(875cm à 1125cm (25cases+2))
	this->setZoneBlocked(975, 875, 250, 250);
		//Poteau droit
			// X(de 1775cm à 2025cm (25 cases+2)) sur Y(875cm à 1125cm (25cases+2))
	this->setZoneBlocked(1775, 875, 250, 250);

		//Bordure de la carte
	//Bordure bas
	this->setZoneBlocked(0, 0, this->width, 1);
	//Bordure haut
	this->setZoneBlocked(0, this->height, this->width, 1);
	//Bordure gauche
	this->setZoneBlocked(0, 0, 1, this->height);
	//Bordure droite
	this->setZoneBlocked(this->width, 0, 1, this->height);

	//Bordure entre la zone du capitaine et la zone de stockage
	//Gauche
	this->setZoneBlocked(0, 1500, 500, 1);
	//Droite
	this->setZoneBlocked(2500, 1500, 500, 1);

	//Régler les CDs
	//Haut gauche et haut droit
	this->setCD(1000, 1500);
	this->setCD(2000, 1500);

	//Bas gauche et bas droit
	this->setCD(450, 300); //Gauche
	this->setCD(2550, 300); //Droit

	//Bas milieu
	this->setCD(1425, 300); //gauche (X approximatif)
	this->setCD(1575, 300); //droit (X approximatif)
	this->setCD(1500, 220); //bas (Y approximatif)
	this->setCD(1500, 220); //haut (Y approximatif)

	//Poteau gauche
	this->setCD(1100, 1240); //haut
	this->setCD(890, 1210); //haut gauche
	this->setCD(1310, 1210); //haut droit
	this->setCD(860, 1000); //milieu gauche
	this->setCD(1100, 760); //bas
	this->setCD(890, 790); //bas gauche
	this->setCD(1310, 790); //bas droit

	//Poteau droite
	this->setCD(1900, 1240); //haut
	this->setCD(1690, 1210); //haut gauche
	this->setCD(2110, 1210); //haut droit
	this->setCD(2140, 1000); //milieu droit
	this->setCD(1900, 760); //bas
	this->setCD(1690, 790); //bas gauche
	this->setCD(2110, 790); //bas droit

}

Map::~Map() {

}

Cell** Map::getZone(int x, int y, int width, int height) {
	Cell** result = NULL;

	int iStart = (int)(x / CELL_WIDTH);
	int jStart = (int)(y / CELL_HEIGHT);

	int iStop = (int)(width / CELL_WIDTH) + iStart;
	int jStop = (int)(height / CELL_HEIGHT) + jStart;

	result = new Cell*[(iStop - iStart)*(jStop - jStart)];
	int currentIndex = 0;

	for(int i = iStart; i < iStop ; i++) {
		for(int j = jStart; j < jStop ; j++) {
			result[currentIndex] = this->map[i][j];
			currentIndex++;
		}
	}

	return result;
}

void Map::setZoneBlocked(int x, int y, int width, int height) {
	Cell** area = this->getZone(x, y, width, height);

	int size = (int)(width / CELL_WIDTH) * (int)(height / CELL_HEIGHT);

	for(int i = 0; i < size ; i++) {
		area[i]->setBlocked(true);
	}
}

void Map::setCD(int x, int y) {
	int i = (int)(x / CELL_WIDTH);
	int j = (int)(y / CELL_HEIGHT);

	this->map[i][j]->setCD(true);
}

Cell* Map::getCell(int x, int y) {
	//On vérifie que l'on est pas hors champs
	if(x < this->width && y < this->height) {
		return this->map[x][y];
	}
	return NULL;
}

Cell* Map::getCellWithDistance(int x, int y) {
	int i = (int)(x / CELL_WIDTH);
	int j = (int)(y / CELL_HEIGHT);

	//On vérifie que l'on est pas hors champs
	if(i < this->width && j < this->height) {
		return this->map[i][j];
	}
	return NULL;
}

Cell** Map::getNeighbors(int x, int y, int range) {
	Cell** result = new Cell*[this->getNeighborsCount(x, y, range)];
	int currentIndex = 0;

	for(int i = x-range ; i <= x+range; i++){
		for(int j = y-range ; j <= y+range ; j++) {
			if(i >= 0 && i < this->width && j >= 0 && j < this->height) {
				if(!(i == x && j == y)) {
					result[currentIndex] = this->map[i][j];
					currentIndex++;
				}
			}
		}

	}

	return result;
}

int Map::getNeighborsCount(int x, int y, int range) {
	int result = 0;

	//Par défaut, c'est laire du carré de longuer (2*range+1) moins le noeud central
	result = (2*range+1)*(2*range+1)-1;

	//Pour chaque cellules, on regarde si elle est hors-champs
	for(int i = x-range ; i <= x+range; i++){
		for(int j = y-range ; j <= y+range ; j++) {
			if(i < 0 || i > this->width || j < 0 || j > this->height) {
				result--;
			}
		}

	}

	return result;
}

Cell* Map::getClosestCD(Cell* begin) {
	Cell* result = NULL;
	double result_cost = 0;

	Cell* temp = NULL;
	double temp_cost = 0;

	//On parcours l'ensemble de la map (peut-être à améliorer) pour trouver le plus proche CD (le résultat est optimal par contre)
	for(int i = 0 ; i < this->width ; i++) {
		for(int j = 0 ; j < this->height ; j++) {
			temp = this->map[i][j];
			temp_cost = sqrt((temp->getX() - begin->getX())*(temp->getX() - begin->getX()) + (temp->getY() - begin->getY())*(temp->getY() - begin->getY()));

			if(temp_cost < result_cost) {
				result = temp;
				result_cost = temp_cost;
			}
		}
	}

	return result;
}

Area* Map::getCaptainAreaLeft() {
	return this->captainAreaLeft;
}
Area* Map::getCaptainAreaRight() {
	return this->captainAreaRight;
}
Area* Map::getStockAreaLeft() {
	return this->stockAreaLeft;
}
Area* Map::getStockAreaRight() {
	return this->stockAreaRight;
}
