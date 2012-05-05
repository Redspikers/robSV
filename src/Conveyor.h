#ifndef __CONVEYOR__
#define __CONVEYOR__

#include <Arduino.h>
#include "Pin.h"

class Conveyor {
	public:
		//Temps durant lequel on laisse tourner le tapis
		static const int RUN_TIME = 4000;

		Conveyor(int pin);
		void action();

	private:
		int pin;

};

#endif
