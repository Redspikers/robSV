#include "Gate.h"

Gate::Gate() {
	this->servoGate = new Servo();
	this->servoGate->attach(GATE_PIN);
}

void Gate::openGate() {
	this->servoGate->write(GATE_ANGLE_OPEN);
}

void Gate::closeGate() {
	this->servoGate->write(GATE_ANGLE_CLOSE);
}

