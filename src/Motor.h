#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>  // Peux etre virer si besoin d'optimisation niveau mémoire : besoin uniquement de cosinus.

class Motor {
	private:
	
		int distanceTotaleRight=0, distanceTotaleLeft=0; //distance parcourue depuis le début du match
		int distanceRight = 0, distanceLeft = 0; //distance parcourue depuis la dernière occurence de la fonction distanceParcourue
		
		int nbPulseRight_temp = 0,  nbPulseLeft_temp =0; //nb d'impulsion temporaire (nb depuis la derniere occurence de distanceParcourue
		
		volatile int countPulseLeft, countPulseRight;
		Servo* servoLeft;
		Servo* servoRight;
		int pos;
		bool attached;

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
		
		void distanceParcourue(int countPulseRight, int countPulseLeft, int distanceRight, int distanceLeft) 

		void distanceTotaleParcourue(int countPulseLeft, int countPulseRight, int distanceTotaleRight, int distanceTotaleLeft)


};

#endif /* MOTOR_H_ */
