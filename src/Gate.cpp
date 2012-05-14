#include "Gate.h"

Gate::Gate() {
	this->servoGate = new Servo();

	this->servoGate->attach(GATE_PIN);
}

void Gate::openGate() {

	this->servoGate->write(Gate::angleOpen);

}

void Gate::closeGate() {

	this->servoGate->write(Gate::angleClose);
}

