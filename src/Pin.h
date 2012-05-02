/*
 * Pin.h
 *
 *  Created on: 1 mai 2012
 *      Author: Koudja
 */


#ifndef PIN_H_
#define PIN_H_

// les roues codeuse sont pas définis ici, c'est normal
// elles sont définis à la dur dans Motor.h parce que c'est legerement différent...
class Pin {
	public:
		static const int CAPTOR_BOTTOM_LEFT = A0;
		static const int CAPTOR_BOTTOM_MIDDLE = A1;
		static const int CAPTOR_BOTTOM_RIGHT = A2;
		static const int CAPTOR_TOP_LEFT = A3;
		static const int CAPTOR_TOP_MIDDLE = A4;
		static const int CAPTOR_TOP_RIGHT = A5;
		static const int CAPTOR_BACK = A6;
		
		static const int SHOULDER = 8;
		static const int ELBOW = 9;
		static const int GATE_LEFT = 11;
		static const int GATE_RIGHT = 10;
		static const int MOTOR_RIGHT = 7;
		static const int MOTOR_LEFT = 6;
		
		
		static const int POMP = 5;
		static const int CONVEYOR = 4;
		static const int JACK = 3;
		
		Pin();
		virtual ~Pin();
};

#endif /* PIN_H_ */
