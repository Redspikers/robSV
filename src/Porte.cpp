#include "Porte.h"

Porte::Porte() {
	this->servoVolet1 = new Servo();
	this->servoVolet2 = new Servo();
	this->ouvert = false;
	this->servoCoude()->attach(PIN_SERVO_COUDE);
	this->servoEpaule()->attach(PIN_SERVO_EPAULE);
	
	this->servoVolet1->attach(PIN_SERVO_VOLET1);
	this->servoVolet2->attach(PIN_SERVO_VOLET2);
}

void Porte::ouvrir() {
	this->servoVolet1->write(180);
	this->servoVolet2->write(180);
	this->ouvert = true;
}

void Porte::fermer() {
	this->servoVolet1->write(90);
	this->servoVolet2->write(90);
	this->ouvert = false;
}

