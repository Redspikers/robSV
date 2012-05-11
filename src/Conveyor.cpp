#include "Conveyor.h"

Conveyor::Conveyor() {
	pinMode(CONVEYOR, OUTPUT);

}

void Conveyor::action() {
	digitalWrite(CONVEYOR, HIGH);
	delay(Conveyor::RUN_TIME);
	digitalWrite(CONVEYOR, LOW);
}

