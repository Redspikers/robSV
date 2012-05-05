#include "Pomp.h"


Pomp::Pomp(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Pomp::compress() {
	digitalWrite(this->pin, HIGH);
	this->compressed = true;
}

void Pomp::drop() {
	digitalWrite(this->pin, LOW);
	this->compressed = false;
}

