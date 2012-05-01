#include "Conveyor.h"


Conveyor::Conveyor() {
	pinMode(Pin::CONVEYOR, OUTPUT);
	
}

void Conveyor::action() {
	digitalWrite(Pin::CONVEYOR, HIGH);
	delay(Conveyor::RUN_TIME);
	digitalWrite(Pin::CONVEYOR, LOW);
}

