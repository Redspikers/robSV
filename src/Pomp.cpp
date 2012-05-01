#include "Pomp.h"


Pomp::Pomp() {
	pinMode(Pin::POMP, OUTPUT);
	
}

void Pomp::compress() {
	digitalWrite(Pin::POMP, HIGH);
	this->compressed = true;
}

void Pomp::drop() {
	digitalWrite(Pin::POMP, LOW);
	this->compressed = false;
}

