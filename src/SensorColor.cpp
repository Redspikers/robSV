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

SensorColor::Color SensorColor::getColor() {
	//TODO
	if (analogRead(COLOR_SENSOR)) {
		return WHITE;
	}

	return OTHER;
}
