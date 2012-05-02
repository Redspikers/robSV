/*
 * Map.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include <math.h>

#include "Cell.h"

class Map {
	public:
		//Create every Cell on the map, store it into map and cds arrays
		Map();
		~Map();

		Cell* getCell(int x, int y);

		//Useful for pathfindings
		Cell** getNeighbors(int x, int y, int range);
		int getNeighborsCount(int x, int y, int range);

		//Return the closest Cell where there is a CD
		Cell* getClosestCD(Cell* begin);

	private:
		//Store all Cell in the map : it is a double array with Cell pointer's
		Cell*** map;
		int lines;
		int columns;

		Cell** captainZoneLeft;
		Cell** captainZoneRight;
		int captainZoneLength;

		Cell** stockZoneLeft;
		Cell** stockZoneRight;
		int stockZoneLength;

};

#endif /* MAP_H_ */
