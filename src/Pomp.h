#ifndef __POMP__
#define __POMP__

#include <Arduino.h>
#include <Servo.h>
#include "Pin.h"

class Pomp {
	public:
		Pomp();
		void compress();
		void drop();

	private:
		boolean compressed; //int pour l'instant

};

#endif //POMP
