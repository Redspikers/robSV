/*
 * main.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include <Arduino.h>

#include "Robot.h"

Robot* robot;

void incrementation_roueCodeuseLeft() {
	robot->getMotor()->incrementation_roueCodeuseLeft();
}

void setup() {
	robot = new Robot();
	attachInterrupt(5, incrementation_roueCodeuseLeft, RISING);
	pinMode( 5 ,  OUTPUT); //pompe
	pinMode( 40 ,  INPUT); //Jack
	pinMode( 46 ,  INPUT); //bouton poussoir
	pinMode(42, OUTPUT);  //Jack (valeur a placer a HIGH)
	pinMode(48, OUTPUT);  // bouton poussoir (valeur a placer a HIGH)
	pinMode(2, OUTPUT);  //Tapis roulant
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
