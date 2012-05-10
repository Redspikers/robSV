/*
 * SensorColor.cpp
 *
 *  Created on: 9 mai 2012
 *      Author: Koudja
 */

#include "SensorColor.h"

SensorColor::SensorColor(int pinNumber) {
	this->pinNumber = pinNumber;
}

SensorColor::~SensorColor() {

}

SensorColor::Color SensorColor::getColor() {
	//TODO
	if(analogRead(this->pinNumber)) {
		return WHITE;
	}

	return OTHER;
}
