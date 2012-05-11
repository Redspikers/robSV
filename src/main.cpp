/*
 * main.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include <Arduino.h>

#include "Pin.h"
#include "Robot.h"

Robot* robot;

void interruptMotorLeft() {
	robot->getMotor()->interruptMotorLeft();
}

void setup() {
	robot = new Robot();
	attachInterrupt(Pin::INTERRUPT_MOTOR_LEFT, interruptMotorLeft, RISING);
	pinMode(Pin::POMP, OUTPUT); //pompe

	pinMode(Pin::JACK, INPUT); //Jack
	pinMode(Pin::PUSH_CD, INPUT); //bouton poussoir

	pinMode(Pin::JACK_HIGH, OUTPUT);  //Jack (valeur a placer a HIGH)
	pinMode(Pin::PUSH_CD_HIGH, OUTPUT);  // bouton poussoir (valeur a placer a HIGH)
	pinMode(Pin::SENSOR_COLOR_HIGH, OUTPUT);  //capteur couleur alim, mettre a HIGH	
	pinMode(Pin::CONVEYOR, OUTPUT);  //Tapis roulant
	
	digitalWrite(Pin::JACK_HIGH, HIGH);
	digitalWrite(Pin::PUSH_CD_HIGH, HIGH);
	digitalWrite(Pin::SENSOR_COLOR_HIGH, HIGH);
}

void loop() {
	robot->loop();
}



int main(void) {
	init();

#if defined(USBCON)
	USB.attach();
#endif

	setup();

	for (;;) {
		loop();
		if (serialEventRun)
			serialEventRun();
	}

	return 0;
}
