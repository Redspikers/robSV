/*
 * Timer.cpp
 *
 *  Created on: 12 mai 2012
 *      Author: Koudja
 */

#include "Timer.h"

Timer::Timer() {
	unsigned long current_millis = millis();

	for(int i = 0; i < MAX_TIMERS; i++) {
		enabled[i] = false;
		callbacks[i] = 0; // if the callback pointer is zero, the slot is free, i.e. doesn't "contain" any timer
		prev_millis[i] = current_millis;
		numRuns[i] = 0;
	}

	numTimers = 0;
}

void Timer::run() {
	int i;
	unsigned long current_millis;

	// get current time
	current_millis = millis();

	for(i = 0; i < MAX_TIMERS; i++) {

		toBeCalled[i] = DEFCALL_DONTRUN;

		// no callback == no timer, i.e. jump over empty slots
		if(callbacks[i]) {

			// is it time to process this timer ?
			if(current_millis - prev_millis[i] >= delays[i]) {

				// update time
				prev_millis[i] = current_millis;

				// check if the timer callback has to be executed
				if(enabled[i]) {

					// "run forever" timers must always be executed
					if(maxNumRuns[i] == RUN_FOREVER) {
						toBeCalled[i] = DEFCALL_RUNONLY;
					}
					// other timers get executed the specified number of times
					else if(numRuns[i] < maxNumRuns[i]) {
						toBeCalled[i] = DEFCALL_RUNONLY;
						numRuns[i]++;

						// after the last run, delete the timer
						if(numRuns[i] >= maxNumRuns[i]) {
							toBeCalled[i] = DEFCALL_RUNANDDEL;
						}
					}
				}
			}
		}
	}

	for(i = 0; i < MAX_TIMERS; i++) {
		switch(toBeCalled[i]) {
			case DEFCALL_DONTRUN:
				break;

			case DEFCALL_RUNONLY:
				(*callbacks[i])();
				break;

			case DEFCALL_RUNANDDEL:
				(*callbacks[i])();
				deleteTimer(i);
				break;
		}
	}
}

// find the first available slot
// return -1 if none found
int Timer::findFirstFreeSlot() {
	int i;

	// all slots are used
	if(numTimers >= MAX_TIMERS) {
		return -1;
	}

	// return the first slot with no callback (i.e. free)
	for(i = 0; i < MAX_TIMERS; i++) {
		if(callbacks[i] == 0) {
			return i;
		}
	}

	// we should never reach this point...
	return -1;
}

int Timer::setTimer(long d, timer_callback f, int n) {
	int freeTimer;

	freeTimer = findFirstFreeSlot();
	if(freeTimer < 0) {
		return -1;
	}

	delays[freeTimer] = d;
	callbacks[freeTimer] = f;
	maxNumRuns[freeTimer] = n;
	enabled[freeTimer] = true;
	prev_millis[freeTimer] = millis();

	numTimers++;

	return freeTimer;
}

int Timer::setInterval(long d, timer_callback f) {
	return setTimer(d, f, RUN_FOREVER);
}

int Timer::setTimeout(long d, timer_callback f) {
	return setTimer(d, f, RUN_ONCE);
}

void Timer::deleteTimer(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return;
	}

	// nothing to delete if no timers are in use
	if(numTimers == 0) {
		return;
	}

	callbacks[numTimer] = 0;
	enabled[numTimer] = false;
	delays[numTimer] = 0;
	numRuns[numTimer] = 0;

	// update number of timers
	numTimers--;
}

// function contributed by code@rowansimms.com
void Timer::restartTimer(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return;
	}

	prev_millis[numTimer] = millis();
}

bool Timer::isEnabled(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return false;
	}

	return enabled[numTimer];
}

void Timer::enable(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return;
	}

	enabled[numTimer] = true;
}

void Timer::disable(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return;
	}

	enabled[numTimer] = false;
}

void Timer::toggle(int numTimer) {
	if(numTimer >= MAX_TIMERS) {
		return;
	}

	enabled[numTimer] = !enabled[numTimer];
}

int Timer::getNumTimers() {
	return numTimers;
}

