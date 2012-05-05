#ifndef __POMP__
#define __POMP__

#include <Arduino.h>
#include <Servo.h>

class Pomp {
	public:
		Pomp(int pin);
		void compress();
		void drop();

	private:
		boolean compressed; //int pour l'instant
		int pin;

};

#endif //POMP
