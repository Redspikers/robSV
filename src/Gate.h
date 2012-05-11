#ifndef GATE_H
#define GATE_H

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"

class Gate {
	public:
		static const int ANGLE_OPEN_RIGHT = 90;
		static const int ANGLE_OPEN_LEFT = 90;
		static const int ANGLE_CLOSE_LEFT = 90;
		static const int ANGLE_CLOSE_RIGHT = 90;

		Gate();
		void closeGate();
		void openGate();

	private:
		Servo* servoGateLeft; //Right et gauche déf par rapport à la marche avant du robot (choix arbitraire)
		Servo* servoGateRight;

};

#endif // GATE_H
