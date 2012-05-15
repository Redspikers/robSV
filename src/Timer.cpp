/*
 * Timer.cpp
 *
 *  Created on: 15 mai 2012
 *      Author: Koudja
 */

#include "Timer.h"

Timer::Timer() {
	this->v_start = 0;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start() {
	this->v_start = millis();
}

bool Timer::isFinish() {
	if(millis() > (this->v_start + DELAY_BEFORE_STOP)) {
		return true;
	}

	return false;
}
