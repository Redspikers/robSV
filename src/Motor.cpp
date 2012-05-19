/*
 * Motor.cpp
 *
 *  Created on: 29 févr. 2012
 *      Author: Koudja
 */

#include "Motor.h"

Motor::Motor() {
	this->distanceTotaleLeft = 0;
	this->distanceLeft = 0;
	this->countPulseLeft = 0;
	this->nbPulseLeft_temp = 0;

	this->servoLeft = new Servo();
	this->servoRight = new Servo();

	this->servoLeft->attach(MOTOR_LEFT);
	this->servoRight->attach(MOTOR_RIGHT);
}

Motor::~Motor() {

}

void Motor::move(int distanceMilliMeter) {
	// servo moteur de 90 a 24 marche avant !
	this->countPulseLeft = 0;
	int i = 0;
	this->acceleration(75);

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

	this->countPulseLeft = 0;
}

void Motor::back(int distanceMilliMeter) {
	this->countPulseLeft = 0;
	// Servo moteur de 90 à 158 : marche arrière
	this->acceleration(110);
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

	this->countPulseLeft = 0;
}

//Le robot ne bouge pas par rapport au terrain,  il se contente de faire une rotation sur place
void Motor::turn(int angleDegree) {
	// 967.12 = perimetre du cercle que parcourt le robot en rotation sur lui même
	if(angleDegree == 0) {

	} else if(angleDegree <= 180) {
		double distanceMilliMeter = ((967.12 / 360) * angleDegree);
		//Acceleration

		this->j = 90;
		for(this->pos = 90; this->pos >= 75; this->pos--) {
			this->servoRight->write(this->j);
			this->servoLeft->write(180 - this->pos);
			if(this->pos % 2 == 0) {
				this->j--;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 100)) {
			delay(5);
		}

		//Deceleration
		this->j = 75;
		for(this->pos = 75; this->pos < 80; this->pos++) {
			this->servoRight->write(this->j);

			this->servoLeft->write(180 - this->pos);
			if(this->pos % 2 == 0) {
				this->j++;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter)) {
			delay(1);
		}

		this->servoRight->write(90);
		this->servoLeft->write(90);
		this->countPulseLeft = 0;

	} else if(angleDegree > 180) {

		double distanceMilliMeter = ((967.12 / 360) * (360 - angleDegree));
		this->j = 90;
		//Acceleration
		for(this->pos = 90; this->pos >= 75; this->pos--) {
			this->servoLeft->write(this->pos);
			this->servoRight->write(180 - this->j);
			if(this->pos % 2 == 0) {
				this->j--;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter - 100)) {
			delay(5);
		}

		this->j = 75;
		//Deceleration
		for(this->pos = 75; this->pos < 80; this->pos++) {
			this->servoLeft->write(this->pos);
			this->servoRight->write(180 - this->j);
			if(this->pos % 2 == 0) {
				this->j++;
			}
			delay(15);
		}

		while(((this->countPulseLeft / 20.25) * 189.028) < (distanceMilliMeter)) {
			delay(1);
		}

		this->servoRight->write(90);
		this->servoLeft->write(90);

	}
	this->countPulseLeft = 0;
}

void Motor::distanceTotaleParcourue(int countPulseRight, int countPulseLeft, int distanceTotaleRight, int distanceTotaleLeft) {
	distanceTotaleLeft = (countPulseLeft / 20.25) * 189.028; //distance en mm
}

int Motor::distanceParcourue(int countPulseLeft, int distanceLeft) {
	distanceLeft = ((countPulseLeft - this->nbPulseLeft_temp) / 20.25) * 189.028; //distance en mm

	this->nbPulseLeft_temp = countPulseLeft;

	return distanceLeft;
}

void Motor::acceleration(int pos) {
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

void Motor::deceleration(int posCourante) {
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
