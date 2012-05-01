/*
 * Motor.cpp
 *
 *  Created on: 29 févr. 2012
 *      Author: Koudja
 */

#include "Motor.h"

Motor::Motor() {
	this->attached = false;

	this->servoLeft = new Servo();
	this->servoRight = new Servo();
}

Motor::~Motor() {

}

void Motor::attach(int pinLeft, int pinRight) {
	this->servoLeft->attach(pinLeft);
	this->servoRight->attach(pinRight);

	this->attached = true;
}

void Motor::detach() {
	this->servoLeft->detach();
	this->servoRight->detach();

	this->attached = false;
}

bool Motor::isAttached() {
	return this->attached;
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
			for (pos = 90; pos < 120; pos++) {
				this->servoRight->write(pos);
				delay(15);
			}
		} else {
			// le servo va reculer
			for (pos = 90; pos < 60; pos--) {
				this->servoRight->write(pos);
				delay(15);
			}
		}
	} else if (servoChoisi == 1) {
		//le servo qui va se mettre en marceh est le gauche
		//le servo va aller vers l'avant
		if (direction == 1) {
			for (pos = 90; pos < 120; pos++) {
				this->servoLeft->write(pos);
				delay(15);
			}
			// le servo va reculer
		} else {
			for (pos = 90; pos < 60; pos--) {
				this->servoLeft->write(pos);
				delay(15);
			}
		}

	}
}


void Motor::move(int distanceMilliMeter) {
	// servo moteur de 90 a 158 marche avant !
	// Cette boucle fait passer la vitesse des moteur de 90 a 120 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (pos = 90; pos < 120; pos++) {
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}

	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	// Cette boucle fait passer la vitesse des moteur de 120 à 90 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (pos = 120; pos < 90; pos--) {
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}

}

void Motor::back(int distanceMilliMeter) {
	// Servo moteur de 90 à 24 : marche arrière
	// Cette boucle fait passer la vitesse des moteur de 90 a 60 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (pos = 90; pos < 60; pos--) {
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15); //Delay qui evite les glissements.
	}
	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	// Cette boucle fait passer la vitesse des moteur de 60 a 90 en evitant les glissements.
	// Distance parcourue pendant cette boucle : A EVALUER
	for (pos = 60; pos < 90; pos++) {
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}
}

// de 0° a 90° angle vers la droite du robot
//de 91° a 180° angel vers la gauche du robot
//
void Motor::turn(int angleDegree, int distanceMilliMeter) {
	// angle vers la droite du robot
	if (angleDegree < 90) {
		int alpha = 90 - angleDegree;
		distanceRight = 15.97 * sqrt(1 - cos(alpha));
		distanceLeft = (distanceRight * 308) / 127.58;
		//Lancer les deux servo à 120 puis les arreter en différé pour gerer
		//le differentiel de distance a parcourir   ??? Bonne idée, ou pas, a voir
		for (pos = 90; pos < 120; pos++) {
			this->servoRight->write(pos);
			this->servoLeft->write(pos);
			delay(15);
		}

		// TODO : gérer le differentiel de distance entre les roues droites et gauches
	}

}

void distanceTotaleParcourue(int countPulseRight, int countPulseLeft, int distanceTotaleRight, int distanceTotaleLeft)
{
	
	distanceTotaleRight = (countPulseRight / 20.25 ) * 189.028 ; //distance en mm
	distanceTotaleLeft = (countPulseLeft / 20.25 ) * 189.028 ;  //distance en mm
	
	
}


void distanceParcourue(int countPulseRight, int countPulseLeft, int distanceRight, int distanceLeft) 
{
	
	
	distanceRight = (( countPulseRight - nbPulseRight_temp ) / 20.25 ) * 189.028 ;  //distance en mm
	distanceLeft = (( countPulseLeft - nbPulseLeft_temp ) / 20.25 ) * 189.028 ;  //distance en mm
	
	
	
	// nbPulse(Left et Right)_temp reçoivent le nb d'impulsion. Ainsi a l' occurence n+1 de cette fonction
	// ces variables seront le nb d'impulsion lors de l'occurence n de cette fonction
	nbPulseRight_temp = countPulseRight;
	nbPulseLeft_temp = countPulseLeft;
	
	
}


void incrementation_roueCodeuseLeft()

{	
	countPulseLeft++;	
}

void incrementation_roueCodeuseRight ()

{
	countPulseRight++;
}


