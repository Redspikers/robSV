/*
 * Map.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Map.h"

Map::Map() {
	//Construction de la map
	//DEBUG : Aucun obstacle
	this->lines = 10;
	this->columns = 10;

	this->map = new Node**[this->lines];

	for(int i=0 ; i < this->lines ;i++) {
		this->map[i] = new Node*[this->columns];

		for(int j=0 ; j < this->columns ;j++) {
			this->map[i][j] = new Node(i, j, false);
		}
	}
}

Map::~Map() {

}

Node* Map::getNode(int x, int y) {
	//On vérifie que l'on est pas hors champs
	if(x < this->lines && y < this->columns) {
		return this->map[x][y];
	}
	return NULL;
}

Node** Map::getNeighbors(int x, int y) {
	Node** result = NULL;
	if(x < this->lines && y < this->columns) {
		if(x < this->lines && y < this->columns) {
				if(x == 0 && y == 0) {
					result = new Node*[3];
					result[0] = this->map[0][1];
					result[1] = this->map[1][0];
					result[2] = this->map[1][1];
				} else if(x == 0 && y == this->columns - 1) {
					result = new Node*[3];
					result[0] = this->map[0][this->columns - 2];
					result[1] = this->map[1][this->columns - 1];
					result[2] = this->map[1][this->columns - 2];
				} else if(x == this->lines - 1 && y == 0) {
					result = new Node*[3];
					result[0] = this->map[this->lines - 1][1];
					result[1] = this->map[this->lines - 2][0];
					result[2] = this->map[this->lines - 2][1];
				} else if(x == this->lines - 1 && y == this->columns - 1) {
					result = new Node*[3];
					result[0] = this->map[this->lines - 1][this->columns - 2];
					result[1] = this->map[this->lines - 2][this->columns - 1];
					result[2] = this->map[this->lines - 2][this->columns - 2];
				} else {
					if(x == 0) {
						result = new Node*[5];
						result[0] = this->map[0][y-1];
						result[1] = this->map[0][y+1];
						result[2] = this->map[1][y-1];
						result[3] = this->map[1][y];
						result[4] = this->map[1][y+1];
					} else if(x == this->lines - 1) {
						result = new Node*[5];
						result[0] = this->map[this->lines - 1][y-1];
						result[1] = this->map[this->lines - 1][y+1];
						result[2] = this->map[this->lines - 2][y-1];
						result[3] = this->map[this->lines - 2][y];
						result[4] = this->map[this->lines - 2][y+1];
					} else if(y == 0) {
						result = new Node*[5];
						result[0] = this->map[x-1][0];
						result[1] = this->map[x+1][0];
						result[2] = this->map[x-1][1];
						result[3] = this->map[x][1];
						result[4] = this->map[x+1][1];
					} else if(y == this->columns - 1) {
						result = new Node*[5];
						result[0] = this->map[x-1][this->columns - 1];
						result[1] = this->map[x+1][this->columns - 1];
						result[2] = this->map[x-1][this->columns - 2];
						result[3] = this->map[x][this->columns - 2];
						result[4] = this->map[x+1][this->columns - 2];
					} else {
						result = new Node*[8];
						result[0] = this->map[x-1][y-1];
						result[1] = this->map[x-1][y];
						result[2] = this->map[x-1][y+1];
						result[3] = this->map[x][y-1];
						result[4] = this->map[x][y+1];
						result[5] = this->map[x+1][y-1];
						result[6] = this->map[x+1][y];
						result[7] = this->map[x+1][y+1];
					}
				}
			}
	}

	return result;
}

int Map::getNeighborsCount(int x, int y) {
	int result = 0;

	if(x < this->lines && y < this->columns) {
		if(x == 0 && y == 0) {
			result = 3;
		} else if(x == 0 && y == this->columns - 1) {
			result = 3;
		} else if(x == this->lines - 1 && y == 0) {
			result = 3;
		} else if(x == this->lines - 1 && y == this->columns - 1) {
			result = 3;
		} else {
			if(x == 0) {
				result = 5;
			} else if(x == this->lines - 1) {
				result = 5;
			} else if(y == 0) {
				result = 5;
			} else if(y == this->columns - 1) {
				result = 5;
			} else {
				result = 8;
			}
		}
	}

	return result;
}
