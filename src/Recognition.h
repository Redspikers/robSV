/*
 * Recognition.h
 *
 *  Created on: 1 mai 2012
 *      Author: claude
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Sensor.h"
#include "Pin.h"

#define ANGLE_BETWEEN_CAPTOR 40
#define ALLOW_ERROR 40

class Recognition {
	public:
		enum Obstacle {
			CD, OHTER, NONE, UNDEFINED
		};

		Recognition();

		void updateValues();
		bool around(int value1, int value2, int ecartmax);
		bool isBetween(int min, int max, int value);
		int* getObstacles();
		void analyse();


		bool hasWallAhead();
		bool hasWallInFront();

		int getDistanceBL();

	private:
		Sensor* captorBL;
		Sensor* captorBM;
		Sensor* captorBR;

		Sensor* captorTL;
		Sensor* captorTM;
		Sensor* captorTR;

		Sensor* captorBack;

		int* valeur;
		int* distancesObstacles;

		SensorConversion* conversion;

};

#endif /* SENSOR_H_ */
