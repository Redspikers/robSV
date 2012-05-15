#include "Conveyor.h"

Conveyor::Conveyor() {

}

void Conveyor::action() {
	digitalWrite(CONVEYOR, LOW);
	delay(Conveyor::RUN_TIME);
	digitalWrite(CONVEYOR, HIGH);
}

void Conveyor::stop() {
	digitalWrite(CONVEYOR, HIGH);
}

