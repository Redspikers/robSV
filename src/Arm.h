#ifndef __ARM__
#define __ARM__

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Definition.h"
#include "Pomp.h"
#include "SensorColor.h"

class Arm {
	public:
		Arm();
		void takeCD();
		void dropInside();
		void idle();
		void idleBegin();

		bool hasCD();

	private:
		Servo* servoElbow;
		Servo* servoShoulder;
		Pomp* pomp;
		SensorColor* sensor;
};

#endif
