#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"

Servo *test;

int main(void) {
	setup();

	for (;;)
		loop();

	return 0;
}

void setup() {
	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(13, OUTPUT);

	test = new Servo();
	test->attach(8);

}

void loop() {
	digitalWrite(13, HIGH); // set the LED on
	delay(1000); // wait for a second
	digitalWrite(13, LOW); // set the LED off
	delay(1000); // wait for a second

	//test->write(1);

}
