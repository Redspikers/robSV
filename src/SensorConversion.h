/*
 * SensorConversion.h
 *
 *  Created on: 6 mai 2012
 *      Author: Koudja
 */

#ifndef SENSORCONVERSION_H_
#define SENSORCONVERSION_H_

class SensorConversion {
	public:
		SensorConversion();
		~SensorConversion();

		int get(int i, int j);

	private:
		int** conversion;
};

#endif /* SENSORCONVERSION_H_ */
