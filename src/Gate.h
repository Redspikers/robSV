#ifndef GATE_H
#define GATE_H

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Definition.h"

class Gate {
	public:
		Gate();
		void closeGate();
		void openGate();

	private:
		Servo* servoGate;

};

#endif // GATE_H
