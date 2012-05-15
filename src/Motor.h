#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"

class Motor {
	private:
		int distanceTotaleLeft; //distance parcourue depuis le début du match
		int distanceLeft; //distance parcourue depuis la dernière occurence de la fonction distanceParcourue

		int nbPulseLeft_temp; //nb d'impulsion temporaire (nb depuis la derniere occurence de distanceParcourue

		volatile int countPulseLeft;

		Servo* servoLeft;
		Servo* servoRight;
		int pos;
		int j;
	public:
		Motor();
		~Motor();

		void acceleration(int pos);

		void back(int distanceMM);
		void move(int distanceMM);
		void turn(int angleDegree);
		void stop();

		void servoUnique(bool servoChoisi, bool direction, int distanceMilliMeter);
		int distanceParcourue(int countPulseLeft, int distanceLeft);
		void distanceTotaleParcourue(int countPulseLeft, int countPulseRight, int distanceTotaleRight, int distanceTotaleLeft);
		void interruptMotorLeft();
		void deceleration(int posCourante);

};

#endif /* MOTOR_H_ */
