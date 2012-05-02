/*
 * Pin.h
 *
 *  Created on: 1 mai 2012
 *      Author: Koudja
 */
//hello

#ifndef PIN_H_
#define PIN_H_

class Pin {
	public:
		static const int CAPTOR = 1;
		static const int SHOULDER = 2;
		static const int ELBOW = 3;
		static const int GATE_LEFT = 4;
		static const int GATE_RIGHT = 5;
		static const int POMP = 6;
		static const int CONVEYOR = 7;

		Pin();
		virtual ~Pin();
};

#endif /* PIN_H_ */
