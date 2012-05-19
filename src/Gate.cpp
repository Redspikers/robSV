#include "Gate.h"

Gate::Gate() {
	this->servo = new Servo();
	this->servo->attach(GATE_PIN);
}

void Gate::open() {
	this->servo->write(GATE_ANGLE_OPEN);
}

void Gate::close() {
	this->servo->write(GATE_ANGLE_CLOSE);
}

