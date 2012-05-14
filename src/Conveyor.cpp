#include "Conveyor.h"

Conveyor::Conveyor() {

}

void Conveyor::action() {
	digitalWrite(CONVEYOR, HIGH);
	delay(Conveyor::RUN_TIME);
	digitalWrite(CONVEYOR, LOW);
}



void Conveyor::stop() {
	digitalWrite(CONVEYOR, LOW);
}


