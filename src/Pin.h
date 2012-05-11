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
		//TODO Capteur analogique
		static const int SENSOR_BOTTOM_LEFT = 22;
		static const int SENSOR_BOTTOM_MIDDLE = 23;
		static const int SENSOR_BOTTOM_RIGHT = 24;
		static const int SENSOR_TOP_LEFT = 25;
		static const int SENSOR_TOP_MIDDLE = 26;
		static const int SENSOR_TOP_RIGHT = 27;
		static const int SENSOR_BACK = 28;

		static const int COLOR_SENSOR = 29; //TODO
		static const int CONVEYOR = 30; //TODO
		
		static const int GATE_LEFT = 11;
		static const int GATE_RIGHT = 10;
		static const int ELBOW = 9;
		static const int SHOULDER = 8;
		static const int MOTOR_RIGHT = 7;
		static const int MOTOR_LEFT = 6;
		
		static const int POMP = 5;
		static const int JACK = 4;
		static const int PUSH_CD = 3;

		static const int INTERRUPT_MOTOR_LEFT = 5;

		Pin();
		virtual ~Pin();
};

#endif /* PIN_H_ */
