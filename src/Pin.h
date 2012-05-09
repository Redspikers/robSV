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
		//TODO Remplacer les Pin
		static const int SENSOR_BOTTOM_LEFT = 12;
		static const int SENSOR_BOTTOM_MIDDLE = 13;
		static const int SENSOR_BOTTOM_RIGHT = 14;
		static const int SENSOR_TOP_LEFT = 15;
		static const int SENSOR_TOP_MIDDLE = 16;
		static const int SENSOR_TOP_RIGHT = 17;
		static const int SENSOR_BACK = 18;
		
		static const int SHOULDER = 8;
		static const int ELBOW = 9;
		static const int GATE_LEFT = 11;
		static const int GATE_RIGHT = 10;
		static const int MOTOR_RIGHT = 7;
		static const int MOTOR_LEFT = 6;
		
		static const int POMP = 5;
		static const int CONVEYOR = 4;
		static const int PUSH_CD = 2; //TODO
		static const int COLOR_SENSOR = 1; //TODO

		static const int JACK = 3;
		
		Pin();
		virtual ~Pin();
};

#endif /* PIN_H_ */
