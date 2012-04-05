#include "Pompe.h"


Pompe::Pompe() {
	pinMode(PIN_POMPE, OUTPUT);
	
}

void Pompe::compresser() {
	digitalWrite(PIN_POMPE, HIGH);
	this->compressee = true;
}

void Pompe::relacher() {
	digitalWrite(PIN_POMPE, LOW);
	this->compressee = false;
}

