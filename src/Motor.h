#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"

//Temps du robot pour faire une rotation relative de 90° vers la droite ou vers la gauche (en milliSecondes)
//moins le temps de d'acceleration et de deceleration
#define TEMPS_ROTATION90 1.0

class Motor {
	private:

		//int distanceTotaleRight;
		int distanceTotaleLeft; //distance parcourue depuis le début du match
		//int distanceRight;
		int distanceLeft; //distance parcourue depuis la dernière occurence de la fonction distanceParcourue

		//int nbPulseRight_temp;
		int nbPulseLeft_temp; //nb d'impulsion temporaire (nb depuis la derniere occurence de distanceParcourue

		volatile int countPulseLeft;
		//int countPulseRight;

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

		void servoUnique(bool servoChoisi, bool direction, int distanceMilliMeter);
		int distanceParcourue(int countPulseLeft, int distanceLeft);
		void distanceTotaleParcourue(int countPulseLeft, int countPulseRight, int distanceTotaleRight, int distanceTotaleLeft);
		void interruptMotorLeft();
		//void incrementation_roueCodeuseRight();
		void deceleration(int posCourante);

};

#endif /* MOTOR_H_ */
