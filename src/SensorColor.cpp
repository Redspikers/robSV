/*
 * SensorColor.cpp
 *
 *  Created on: 9 mai 2012
 *      Author: Koudja
 */

#include "SensorColor.h"

SensorColor::SensorColor() {

}

SensorColor::~SensorColor() {

}

bool SensorColor::isWhite() {
	//TODO
	if(analogRead(COLOR_SENSOR) > VAL_ANALOG_WHITE) {
		return true;
	}

	return false;
}
