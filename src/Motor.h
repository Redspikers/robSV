#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>  // Peux etre virer si besoin d'optimisation niveau mémoire : besoin uniquement de cosinus.

class Motor {
	private:
		Servo* servoLeft;
		Servo* servoRight;
		int pos;
		bool attached;
		int distanceRight;
		int distanceLeft;

	public:
		Motor();
		virtual ~Motor();

		void attach(int pinLeft, int pinRight);
		void detach();
		bool isAttached();
		void back(int distanceMM);
		void move(int distanceMM);
		void turn(int angleDegree, int distanceMM);
		void servoUnique(bool servoChoisi, bool direction, int distanceMilliMeter);
};

#endif /* MOTOR_H_ */
