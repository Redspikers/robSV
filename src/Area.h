/*
 * Area.h
 *
 *  Created on: 10 mai 2012
 *      Author: Koudja
 */

#ifndef AREA_H_
#define AREA_H_

#include "Cell.h"

class Area {
	public:
		Area(Cell** cells, Cell* center, int size);
		~Area();

		Cell** getCells();
		int getSize();
		void setBlocked();
		int countCD();
		void addCD(int num);
		Cell* getCenter();

	private:
		Cell** cells;
		Cell* center;
		int size;
		int cds;
};

#endif /* AREA_H_ */
