/*
 * Map.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Map.h"

Map::Map() {
	//Construction de la map

	//Taille des noeuds : 10cm par 10cm (total 2m par 3m)
	this->lines = 20;
	this->columns = 30;

	this->map = new Cell**[this->lines];

	//Initialisation
	for(int i=0 ; i < this->lines ;i++) {
		this->map[i] = new Cell*[this->columns];

		for(int j=0 ; j < this->columns ;j++) {
			this->map[i][j] = new Cell(i, j, false);
		}
	}

	//Régler les obstacles fixes
	//TODO
	this->map[4][5]->setBlocked(true);

	//Régler les CDs
	//TODO

}

Map::~Map() {

}

Cell* Map::getCell(int x, int y) {
	//On vérifie que l'on est pas hors champs
	if(x < this->lines && y < this->columns) {
		return this->map[x][y];
	}
	return NULL;
}

Cell** Map::getNeighbors(int x, int y, int range) {
	Cell** result = new Cell*[this->getNeighborsCount(x, y, range)];
	int currentIndex = 0;

	for(int i = x-range ; i <= x+range; i++){
		for(int j = y-range ; j <= y+range ; j++) {
			if(i >= 0 && i < this->lines && j >= 0 && j < this->columns) {
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
			if(i < 0 || i > this->lines || j < 0 || j > this->columns) {
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
	for(int i = 0 ; i < this->lines ; i++) {
		for(int j = 0 ; j < this->columns ; j++) {
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
