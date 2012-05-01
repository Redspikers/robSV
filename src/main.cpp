/*
 * main.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include <Arduino.h>

#include "AStarLight.h"
#include "Map.h"

void setup() {

}

void loop() {

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
