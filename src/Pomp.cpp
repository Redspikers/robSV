#include "Pomp.h"

Pomp::Pomp() {

}

void Pomp::compress() {
	digitalWrite(POMP, HIGH);
	this->compressed = true;
	//Léger delay pour être sur que la pomp a pris
	delay(50);
}

void Pomp::drop() {
	digitalWrite(POMP, LOW);
	this->compressed = false;
}

