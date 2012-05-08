/*
 * Map.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Map.h"

Map::Map() {
	//Variables pour boucle for (économie de mémoire)
	int i = 0;
	int j = 0;
	int current = 0;

	//Construction de la map
	//Taille des noeuds : 10cm par 10cm (total 2m par 3m)
	this->lines = 20;
	this->columns = 30;

	this->map = new Cell**[this->lines];

	//Initialisation
	for(i=0 ; i < this->lines ;i++) {
		this->map[i] = new Cell*[this->columns];

		for(j=0 ; j < this->columns ;j++) {
			this->map[i][j] = new Cell(i, j, false);
		}
	}

	//Construction des zones
	this->captainZoneLength = 250;
	this->stockZoneLength = 25;

		//Capitaine gauche
	this->captainZoneLeft = new Cell*[this->captainZoneLength];
	current = 0;
			// X(de 0cm à 500mm (50 cases)) sur Y(1500mm à 2000mm (5cases))
	for(i = 0; i < 5 ; i++) {
		for(j = 15; j < 20 ; j++) {
			this->captainZoneLeft[current] = this->map[i][j];
			current++;
		}
	}

		//Câle gauche
	this->stockZoneLeft = new Cell*[this->stockZoneLength];
	current = 0;
			// X(de 0mm à 400mm (4 cases)) sur Y(750mm à 1500mm (7cases))
	for(i = 0; i < 4 ; i++) {
		for(j = 8; j < 14 ; j++) {
			this->stockZoneLeft[current] = this->map[i][j];
			current++;
		}
	}

		//Capitaine droite
	this->captainZoneRight = new Cell*[this->captainZoneLength];
	current = 0;
			// X(de 2500mm à 3000mm (5 cases)) sur Y(1500mm à 2000mm (5cases))
	for(i = 25; i < 30 ; i++) {
		for(j = 15; j < 20 ; j++) {
			this->captainZoneRight[current] = this->map[i][j];
			current++;
		}
	}

		//Câle droite
	this->stockZoneRight = new Cell*[this->stockZoneLength];
	current = 0;
			// X(de 2600mm à 3000mm (4 cases)) sur Y(750mm à 1500mm (7cases))
	for(i = 26; i < 30 ; i++) {
		for(j = 8; j < 14 ; j++) {
			this->stockZoneRight[current] = this->map[i][j];
			current++;
		}
	}


	//Régler les obstacles fixes
		//Câle avec couvercle : on n'y rentre pas !
		//Partie gauche
			// X(de 0mm à 400mm (4 cases)) sur Y(0cm à 750mm (7cases))
	for(i = 0; i < 4 ; i++) {
		for(j = 0; j < 7 ; j++) {
			this->map[i][j]->setBlocked(true);
		}
	}
		//Partie droite
			// X(de 2600mm à 3000mm (4 cases)) sur Y(0mm à 750mm (7cases))
	for(i = 26; i < 30 ; i++) {
		for(j = 0; j < 7 ; j++) {
			this->map[i][j]->setBlocked(true);
		}
	}

		//Poteau gauche
			// X(de 975cm à 1225cm (25 cases+2)) sur Y(875cm à 1125cm (25cases+2))
	for(i = 97; i < 123 ; i++) {
		for(j = 87; j < 113 ; j++) {
			this->map[i][j]->setBlocked(true);
		}
	}
		//Poteau droit
			// X(de 1775cm à 2025cm (25 cases+2)) sur Y(875cm à 1125cm (25cases+2))
	for(i = 178; i < 203 ; i++) {
		for(j = 87; j < 113 ; j++) {
			this->map[i][j]->setBlocked(true);
		}
	}

		//Bordure de la carte
	//Bordure haut et bas
	for(j = 0; j < this->columns ; j++) {
		this->map[0][j]->setBlocked(true);
		this->map[this->lines-1][j]->setBlocked(true);
	}
	//Bordure gauche et droite
	for(i = 0; i < this->lines ; i++) {
		this->map[i][0]->setBlocked(true);
		this->map[i][this->columns-1]->setBlocked(true);
	}

	//Bordure entre la zone du capitaine et la zone de stockage
	//Gauche
	for(i=0 ; i < 5 ; i++) {
		this->map[i][14]->setBlocked(true);
	}
	//Droite
	for(i=25 ; i < 30 ; i++) {
		this->map[i][14]->setBlocked(true);
	}

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
