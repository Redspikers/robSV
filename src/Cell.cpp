/*
 * Cell.cpp
 *
 *  Created on: 29 avr. 2012
 *      Author: Koudja
 */

#include "Cell.h"

Cell::Cell(int x, int y, bool blocked) {
	this->x = x;
	this->y = y;
	this->blocked = blocked;

	this->cd = false;
	this->robot = false;
}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

void Cell::setX(int x) {
	this->x = x;
}

int Cell::getX() {
	return this->x;
}

void Cell::setY(int y) {
	this->y = y;
}

int Cell::getY() {
	return this->y;
}


void Cell::setBlocked(bool blocked) {
	this->blocked = blocked;
}

bool Cell::isBlocked() {
	return this->blocked;
}

void Cell::setCD(bool cd) {
	this->cd = cd;
}

bool Cell::hasCD() {
	return this->cd;
}

void Cell::setRobot(bool robot) {
	this->robot = robot;
}

bool Cell::hasRobot() {
	return this->robot;
}
