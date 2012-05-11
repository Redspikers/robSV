#include "Pomp.h"

Pomp::Pomp() {
	pinMode(POMP, OUTPUT);
}

void Pomp::compress() {
	digitalWrite(POMP, HIGH);
	this->compressed = true;
}

void Pomp::drop() {
	digitalWrite(POMP, LOW);
	this->compressed = false;
}

