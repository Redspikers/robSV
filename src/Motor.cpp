/*
 * Motor.cpp
 *
 *  Created on: 29 févr. 2012
 *      Author: Koudja
 */

#include "Motor.h"

Motor::Motor() {
	//this->distanceTotaleRight=0;
	this->distanceTotaleLeft = 0;
	//this->distanceRight = 0;
	this->distanceLeft = 0;

	//this->nbPulseRight_temp = 0;
	this->nbPulseLeft_temp = 0;

	this->servoLeft = new Servo();
	this->servoRight = new Servo();

	this->servoLeft->attach(MOTOR_LEFT);
	this->servoRight->attach(MOTOR_RIGHT);
}

Motor::~Motor() {

}

//METHODE SUIVANTE INUTILE

/*
 //Fonction qui va faire tourner un seul servo à la distance a aprcourir voulu
 //Fonction qui prend le servo a faire tourner : 0 pour droite 
 //												1 pour gauche

 // 			prend la direction :				1 pour marche avant
 //												0 pour marche arrière
 //			prend la distanceMM a parcourir avec ce servo 
 void Motor::servoUnique(bool servoChoisi, bool direction, int distanceMilliMeter) {
 // le servo qui va se mettre en marche est le droit
 if (servoChoisi == 0) {
 //le servo va aller vers l'avant
 if (direction == 1) {
 for (this->pos = 90; this->pos < 120; this->pos++) {
 this->servoRight->write(this->pos);
 delay(15);
 }
 } else {
 // le servo va reculer
 for (this->pos = 90; this->pos < 60; this->pos--) {
 this->servoRight->write(this->pos);
 delay(15);
 }
 }
 } else if (servoChoisi == 1) {
 //le servo qui va se mettre en marceh est le gauche
 //le servo va aller vers l'avant
 if (direction == 1) {
 for (this->pos = 90; this->pos < 120; this->pos++) {
 this->servoLeft->write(this->pos);
 delay(15);
 }
 // le servo va reculer
 } else {
 for (this->pos = 90; this->pos < 60; this->pos--) {
 this->servoLeft->write(this->pos);
 delay(15);
 }
 }

 }
 }*/

void Motor::move(int distanceMilliMeter) {
	// servo moteur de 90 a 24 marche avant !
	this->countPulseLeft = 0;
	int i;
	acceleration(75);
	while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 150)) {
		delay(5);
	}

	for(i = 75; i < 83; i++) {
		this->servoRight->write(i);
		this->servoLeft->write(i - 1);
		delay(15);
	}

	while(((this->countPulseLeft / 20.25) * 189.028) < distanceMilliMeter) {
		delay(1);
	}

	this->servoRight->write(90);
	this->servoLeft->write(90);

	countPulseLeft = 0;
}

void Motor::back(int distanceMilliMeter) {
	// Servo moteur de 90 à 158 : marche arrière

	acceleration(110);
	while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 150)) {
		delay(5);
	}

	for(int i = 110; i >= 97; i--) {
		this->servoRight->write(i);
		this->servoLeft->write(i + 1);
		delay(15);
	}

	while(((this->countPulseLeft / 20.25) * 189.028) < distanceMilliMeter) {
		delay(1);
	}

	this->servoRight->write(90);
	this->servoLeft->write(90);

	countPulseLeft = 0;
}

//Le robot ne bouge pas par rapport au terrain,  il se contente de faire une rotation sur place
void Motor::turn(int angleDegree) {

	// 967.12 = perimetre du cercle que parcourt le robot en rotation sur lui même

	if(angleDegree == 0) {
	}

	//angle vers la gauche du robot
	else if(angleDegree <= 180) {

		double distanceMilliMeter = ((967.12 / 360) * angleDegree);
		//Acceleration

		j = 90;
		for(pos = 90; pos >= 75; pos--) {
			this->servoRight->write(j);
			this->servoLeft->write(180 - pos);
			if(pos % 2 == 0) {
				j--;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 100)) {
			delay(5);
		}

		//Deceleration
		j = 75;
		for(pos = 75; pos < 80; pos++) {
			this->servoRight->write(j);

			this->servoLeft->write(180 - pos);
			if(pos % 2 == 0) {
				j++;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter)) {
			delay(1);
		}

		this->servoRight->write(90);
		this->servoLeft->write(90);
		countPulseLeft = 0;

	}

	//angle vers la droite du robot

	else if(angleDegree > 180) {

		double distanceMilliMeter = ((967.12 / 360) * (360 - angleDegree));
		j = 90;
		//Acceleration
		for(pos = 90; pos >= 75; pos--) {
			this->servoLeft->write(pos);
			this->servoRight->write(180 - j);
			if(pos % 2 == 0) {
				j--;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 100)) {
			delay(5);
		}

		j = 75;
		//Deceleration
		for(pos = 75; pos < 80; pos++) {
			this->servoLeft->write(pos);
			this->servoRight->write(180 - j);
			if(pos % 2 == 0) {
				j++;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter)) {
			delay(1);
		}

		this->servoRight->write(90);
		this->servoLeft->write(90);

	}
	countPulseLeft = 0;
}

void Motor::distanceTotaleParcourue(int countPulseRight, int countPulseLeft, int distanceTotaleRight, int distanceTotaleLeft) {
	//distanceTotaleRight = (countPulseRight / 20.25 ) * 189.028 ; //distance en mm
	distanceTotaleLeft = (countPulseLeft / 20.25) * 189.028; //distance en mm
}

int Motor::distanceParcourue(int countPulseLeft, int distanceLeft) {
	//distanceRight = (( countPulseRight - this->nbPulseRight_temp ) / 20.25 ) * 189.028 ;  //distance en mm
	distanceLeft = ((countPulseLeft - this->nbPulseLeft_temp) / 20.25) * 189.028; //distance en mm

	// nbPulse(Left et Right)_temp reçoivent le nb d'impulsion. Ainsi a l' occurence n+1 de cette fonction
	// ces variables seront le nb d'impulsion lors de l'occurence n de cette fonction
	//this->nbPulseRight_temp = countPulseRight;
	this->nbPulseLeft_temp = countPulseLeft;
	return distanceLeft;
}

void Motor::acceleration(int pos) //accelere de 90 a pos
{
	int i = 0;
	if(pos > 90) {
		for(i = 90; i < pos; i++) {
			this->servoRight->write(i);
			this->servoLeft->write(i + 1);
			delay(15);
		}
	}
	if(pos < 90) {
		for(i = 90; i >= pos; i--) {
			this->servoRight->write(i);
			this->servoLeft->write(i - 1);
			delay(15);
		}
	}
}

void Motor::deceleration(int posCourante) // decelere de posCourante à 90
{
	int i = 0;
	if(posCourante > 90) {
		for(i = posCourante; i >= 90; i--) {
			this->servoRight->write(i);
			this->servoLeft->write(i + 1);
			delay(15);
		}
		this->servoLeft->write(90);
	}
	if(posCourante < 90) {
		for(i = posCourante; i < 90; i++) {
			this->servoRight->write(i);
			this->servoLeft->write(i - 1);
			delay(15);
		}
		this->servoLeft->write(90);
	}
}

void Motor::interruptMotorLeft() {
	this->countPulseLeft++;
}

void Motor::stop() {
	//Arret des moteurs
	this->servoRight->write(90);
	this->servoLeft->write(90);
}

/*
 void Motor::incrementation_roueCodeuseRight() {
 this->countPulseRight++;
 }
 */
