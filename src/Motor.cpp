/*
 * Motor.cpp
 *
 *  Created on: 29 févr. 2012
 *      Author: Koudja
 */

#include "Motor.h"

Motor::Motor() {
	this->attached = false;

	this->servoLeft = new Servo();
	this->servoRight = new Servo();
}

Motor::~Motor() {

}

void Motor::attach(int pinLeft, int pinRight) {
	this->servoLeft->attach(pinLeft);
	this->servoRight->attach(pinRight);

	this->attached = true;
}

void Motor::detach() {
	this->servoLeft->detach();
	this->servoRight->detach();

	this->attached = false;
}

boolean Motor::isAttached() {
	return this->attached;
}

void Motor::move(int distanceMilliMeter) {
	//TODO convertir distance en temps selon la circonférence des roues + glissement + attuenation générale

	//TODO calculer la vitesse réelle
	int speedMillimeterPerSeconds = 100; //1cm par secondes

	int millisecondsMoving = (distanceMilliMeter * speedMillimeterPerSeconds) / 1000;

	this->servoLeft->writeMicroseconds(millisecondsMoving);
	this->servoRight->writeMicroseconds(millisecondsMoving);
}

void Motor::turn(int angleDegree, int distanceMilliMeter) {
	//Même chose que move mais on gère séparemment

	//TODO Calculer l'écart entre les 2 roues motrices puis en déduire l'angle selon la distance parcouru
}

