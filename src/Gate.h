#ifndef GATE_H
#define GATE_H

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"

class Gate {
	public:
		static const int angleOpen = 180;
		static const int angleClose = 0;

		Gate();
		void closeGate();
		void openGate();

	private:
		Servo* servoGate;

};

#endif // GATE_H
