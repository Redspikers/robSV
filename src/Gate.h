#ifndef GATE_H
#define GATE_H

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Definition.h"

class Gate {
	public:
		Gate();
		void close();
		void open();

	private:
		Servo* servo;

};

#endif // GATE_H
