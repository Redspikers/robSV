/*
 * SensorColor.h
 *
 *  Created on: 9 mai 2012
 *      Author: Koudja
 */

#ifndef SENSORCOLOR_H_
#define SENSORCOLOR_H_

#include <Arduino.h>

class SensorColor {
	public:
		enum Color {
			WHITE,
			OTHER
		};

		SensorColor(int pinNumber);
		~SensorColor();

		Color getColor();


	private:
		int pinNumber;
};

#endif /* SENSORCOLOR_H_ */
