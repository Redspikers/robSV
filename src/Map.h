/*
 * Map.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include <newarray.h>

#include "Node.h"

class Map {
	public:
		Map();
		~Map();

		Node* getNode(int x, int y);
		Node** getNeighbors(int x, int y);
		int getNeighborsCount(int x, int y);

	private:
		Node ***map;
		int lines;
		int columns;

};

#endif /* MAP_H_ */
