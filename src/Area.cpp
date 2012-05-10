/*
 * Area.cpp
 *
 *  Created on: 10 mai 2012
 *      Author: Koudja
 */

#include "Area.h"

Area::Area(Cell** cells, Cell* center, int size) {
	this->cells = cells;
	this->center = center;
	this->size = size;
	this->cds = 0;
}

Area::~Area() {

}

Cell** Area::getCells() {
	return this->cells;
}

int Area::getSize() {
	return this->size;
}

void Area::setBlocked() {
	for(int i=0 ; i < this->size ; i++) {
		this->cells[i]->setBlocked(true);
	}
}

int Area::countCD() {
	return this->cds;
}

void Area::addCD(int num) {
	this->cds = this->cds + num;
}

Cell* Area::getCenter() {
	return this->center;
}
