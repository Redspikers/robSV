/*
 * main.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Robot.h"

Robot* robot;

void interruptMotorLeft() {
	robot->getMotor()->interruptMotorLeft();
}

void stop() {
	robot->stop();
}

void setup() {
	robot = new Robot();

	attachInterrupt(INTERRUPT_MOTOR_LEFT, interruptMotorLeft, RISING);
	pinMode(POMP, OUTPUT); //pompe

	pinMode(JACK, INPUT); //Jack
	pinMode(PUSH_CD, INPUT); //bouton poussoir

	pinMode(JACK_HIGH, OUTPUT); //Jack (valeur a placer a HIGH)
	pinMode(PUSH_CD_HIGH, OUTPUT); // bouton poussoir (valeur a placer a HIGH)
	pinMode(SENSOR_COLOR_HIGH, OUTPUT); //capteur couleur alim, mettre a HIGH
	pinMode(CONVEYOR, OUTPUT); //Tapis roulant

	digitalWrite(JACK_HIGH, HIGH);
	digitalWrite(PUSH_CD_HIGH, HIGH);
	digitalWrite(SENSOR_COLOR_HIGH, HIGH);
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

	for(;;) {
		loop();
		if(serialEventRun)
			serialEventRun();
	}

	return 0;
}
