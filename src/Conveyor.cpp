#include "Conveyor.h"


Conveyor::Conveyor(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
	
}

void Conveyor::action() {
	digitalWrite(this->pin, HIGH);
	delay(Conveyor::RUN_TIME);
	digitalWrite(this->pin, LOW);
}

