#ifndef __CAPTOR__
#define __CAPTOR__

#include <Arduino.h>
#include "SensorConversion.h"

class Sensor {
public:
	Sensor(int pinN, SensorConversion* conversion);
	int get();

private:
	int pinNumber;
	SensorConversion* conversion;

};

#endif
