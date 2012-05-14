/*
 * Recognition.h
 *
 *  Created on: 1 mai 2012
 *      Author: claude
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Sensor.h"
#include "SensorBlue.h"
#include "SensorConversion.h"
#include "SensorConversionBlue.h"
#include "Pin.h"

#include "Definition.h"

class Recognition {
	public:
		Recognition();

		bool around(int value1, int value2, int ecartmax);
		bool isBetween(int min, int max, int value);

		bool isWall();
		bool isWallParallel();

		bool isCD();
		bool isObstacle();
		bool isRobot();
		bool isCDInFront();

		int getDistanceBL();
		int getDistanceBM();
		int getDistanceBR();
		int getDistanceTL();
		int getDistanceTM();
		int getDistanceTR();

	private:
		Sensor* captorBL;
		SensorBlue* captorBM;
		Sensor* captorBR;

		Sensor* captorTL;
		Sensor* captorTM;
		Sensor* captorTR;

		SensorConversion* conversion;
		SensorConversionBlue* conversionBlue;

};

#endif /* SENSOR_H_ */
