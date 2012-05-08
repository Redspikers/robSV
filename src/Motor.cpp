/*
 * Motor.cpp
 *
 *  Created on: 29 févr. 2012
 *      Author: Koudja
 */

#include "Motor.h"

Motor::Motor(int pinLeft, int pinRight) {
	this->pinLeft = pinLeft;
	this->pinRight = pinRight;

	this->distanceTotaleRight=0;
	this->distanceTotaleLeft=0;
	this->distanceRight = 0;
	this->distanceLeft = 0;

	this->nbPulseRight_temp = 0;
	this->nbPulseLeft_temp =0;

	this->servoLeft = new Servo();
	this->servoRight = new Servo();

	this->servoLeft->attach(this->pinLeft);
	this->servoRight->attach(this->pinRight);
}

Motor::~Motor() {

}

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
}


void Motor::move(int distanceMilliMeter) {
	// servo moteur de 90 a 158 marche avant !
	// Cette boucle fait passer la vitesse des moteur de 90 a 120 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (this->pos = 90; this->pos < 120; this->pos++) {
		this->servoRight->write(this->pos);
		this->servoLeft->write(this->pos);
		delay(15);
	}

	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	// Cette boucle fait passer la vitesse des moteur de 120 à 90 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (this->pos = 120; this->pos < 90; this->pos--) {
		this->servoRight->write(this->pos);
		this->servoLeft->write(this->pos);
		delay(15);
	}

}

void Motor::back(int distanceMilliMeter) {
	// Servo moteur de 90 à 24 : marche arrière
	// Cette boucle fait passer la vitesse des moteur de 90 a 60 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (this->pos = 90; this->pos < 60; this->pos--) {
		this->servoRight->write(this->pos);
		this->servoLeft->write(this->pos);
		delay(15); //Delay qui evite les glissements.
	}
	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	// Cette boucle fait passer la vitesse des moteur de 60 a 90 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (this->pos = 60; this->pos < 90; this->pos++) {
		this->servoRight->write(this->pos);
		this->servoLeft->write(this->pos);
		delay(15);
	}
}

// de 0° a 90° angle vers la droite du robot
//de 91° a 180° angle vers la gauche du robot
//Le robot ne bouge pas par rapport au terrain,  il se contente de faire une rotation sur place
//Peut etre faudra-t-il enlever les etapes d'acceleration et deceleration : on aura une vitesse basse de rotation
//mais une meilleure precision
void Motor::turnOnSpot(int angleDegree) {
	int alpha = 90-angleDegree;

	// angle vers la droite du robot
	if (angleDegree < 90) {

		//Acceleration
		for (pos = 90; pos < 120; pos++) {
			this->servoRight->write(pos);
			this->servoLeft->write(180-pos);
			delay(15);
		}
		
		delay((int)(TEMPS_ROTATION90*(90/alpha)));//Formule à revoir !!
		
		//Deceleration
		for (pos=119; pos >= 90; pos--) {
			this->servoRight->write(pos);
			this->servoLeft->write(180-pos);
			delay(15);
		}
	}
	//idem pour l'autre sens, tester d'abord pour angleDegree < 90	
}

void Motor::distanceTotaleParcourue(int countPulseRight, int countPulseLeft, int distanceTotaleRight, int distanceTotaleLeft) {
	distanceTotaleRight = (countPulseRight / 20.25 ) * 189.028 ; //distance en mm
	distanceTotaleLeft = (countPulseLeft / 20.25 ) * 189.028 ;  //distance en mm
}


void Motor::distanceParcourue(int countPulseRight, int countPulseLeft, int distanceRight, int distanceLeft) {
	distanceRight = (( countPulseRight - this->nbPulseRight_temp ) / 20.25 ) * 189.028 ;  //distance en mm
	distanceLeft = (( countPulseLeft - this->nbPulseLeft_temp ) / 20.25 ) * 189.028 ;  //distance en mm
	
	// nbPulse(Left et Right)_temp reçoivent le nb d'impulsion. Ainsi a l' occurence n+1 de cette fonction
	// ces variables seront le nb d'impulsion lors de l'occurence n de cette fonction
	this->nbPulseRight_temp = countPulseRight;
	this->nbPulseLeft_temp = countPulseLeft;
}


void Motor::incrementation_roueCodeuseLeft() {
	this->countPulseLeft++;
}

void Motor::incrementation_roueCodeuseRight() {
	this->countPulseRight++;
}
