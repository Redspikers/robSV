/*
 * Timer.h
 *
 *  Created on: 15 mai 2012
 *      Author: Koudja
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>
#include "Definition.h"

class Timer {
	public:
		Timer();
		~Timer();

		void start();
		bool isFinish();

	private:
		int v_start;

};

#endif /* TIMER_H_ */
