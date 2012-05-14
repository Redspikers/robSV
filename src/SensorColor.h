/*
 * SensorColor.h
 *
 *  Created on: 9 mai 2012
 *      Author: Koudja
 */

#ifndef SENSORCOLOR_H_
#define SENSORCOLOR_H_

#include <Arduino.h>
#include "Pin.h"
#include "Definition.h"

class SensorColor {
	public:

		SensorColor();
		~SensorColor();

		bool isWhite();
};

#endif /* SENSORCOLOR_H_ */
