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
#include "Area.h"

class Map {
	public:
		static const int CELL_WIDTH = 50;
		static const int CELL_HEIGHT = 50;
		//Permet d'éviter de refaire le calcul à chaque fois !
		//70.71mm pour être exact
		static const int CELL_DIAGONAL = 71;

		//Create every Cell on the map, store it into map and cds arrays
		Map();
		~Map();

		//X and Y are index, not millimeters
		Cell* getCell(int x, int y);
		Cell* getCellWithDistance(int x, int y);

		//Useful for pathfindings, integer is index, not millimeter
		Cell** getNeighbors(int x, int y, int range);
		int getNeighborsCount(int x, int y, int range);

		Cell** getStraights(int x, int y, int range);
		int getStraightsCount(int x, int y, int range);

		//Return the closest Cell where there is a CD
		Cell* getClosestCD(Cell* begin);

		Area* getCaptainAreaLeft();
		Area* getCaptainAreaRight();

		Area* getStockAreaLeft();
		Area* getStockAreaRight();

	private:
		//Store all Cell in the map : it is a double array with Cell pointer's
		Cell*** map;
		int width;
		int height;

		Area* captainAreaLeft;
		Area* captainAreaRight;

		Area* stockAreaLeft;
		Area* stockAreaRight;

		//All integer in millimeter
		Cell** getZone(int x, int y, int width, int height);
		void setZoneBlocked(int x, int y, int width, int height);
		void setCD(int x, int y);

};

#endif /* MAP_H_ */
