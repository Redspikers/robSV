#include "Tapis.h"


Tapis::Tapis() {
	pinMode(PIN_TAPIS, OUTPUT);
	
}

void Tapis::actionner() {
	digitalWrite(PIN_TAPIS, HIGH);
	delay(TEMPS_ACTION); 
	digitalWrite(PIN_TAPIS, LOW);
}

