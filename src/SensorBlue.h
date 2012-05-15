#ifndef __CAPTORBLUE__
#define __CAPTORBLUE_

#include <Arduino.h>
#include "SensorConversionBlue.h"

class SensorBlue {
	public:
		SensorBlue(int pinN, SensorConversionBlue* conversion);
		int get();

	private:
		int pinNumber;
		SensorConversionBlue* conversion;

};

#endif
