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

boolean Motor::isAttached() {
	return this->attached;
}

void Motor::servoUnique( bool servoChoisi, bool direction,  int distanceMilliMeter, )
//Fonction qui va faire tourner un seul servo à la distance a aprcourir voulu
//Fonction qui prend le servo a faire tourner : 0 pour droite 
//												1 pour gauche

// 			prend la direction :				1 pour marche avant
//												0 pour marche arrière
//			prend la distanceMM a parcourir avec ce servo 

{
	if (servoChoisi == 0) // le servo qui va se mettre en marche est le droit
	{
		if (direction == 1) //le servo va aller vers l'avant
		{
			for(pos=90 ; pos < 120; pos++) 
			{
		
				this->servoRight->write(pos);
				delay(15);
			}
		}
		else  // le servo va reculer
		{
			for(pos=90 ; pos < 60; pos--) 
			{
		
				this->servoRight->write(pos);
				delay(15);
			}
		}
	}	
	
	else if (servoChoisi == 1) //le servo qui va se mettre en marceh est le gauche
		{
			if (direction == 1) //le servo va aller vers l'avant
		{
			for(pos=90 ; pos < 120; pos++) 
			{
		
				this->servoLeft->write(pos);
				delay(15);
			}
		}
		else  // le servo va reculer
		{
			for(pos=90 ; pos < 60; pos--) 
			{
		
				this->servoLeft->write(pos);
				delay(15);
			}
		}
		
}

void Motor::move(int distanceMilliMeter) { // servo moteur de 90 a 158 marche avant !
	
	
	for(pos=90 ; pos < 120; pos++) // Cette boucle fait passer la vitesse des moteur de 90 a 120 en evitant les glissements.
									// Distance parcourue pendant cette boucle : A EVALUER
	{
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}
	
	
	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	
	for(pos=120 ; pos < 90; pos--) // Cette boucle fait passer la vitesse des moteur de 120 à 90 en evitant les glissements.
									// Distance parcourue pendant cette boucle : A EVALUER
	{
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}
	
	
}
void Motor::back(int distanceMilliMeter) // Servo moteur de 90 à 24 : marche arrière
{
	
	for(pos=90 ; pos < 60; pos--) // Cette boucle fait passer la vitesse des moteur de 90 a 60 en evitant les glissements.
									// Distance parcourue pendant cette boucle : A EVALUER
	{
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);   //Delay qui evite les glissements.
	}
	// Durée de déplacement à ajouter (avec un delay() ) en fonction de distanceMM
	
	for(pos=60 ; pos < 90; pos++) // Cette boucle fait passer la vitesse des moteur de 60 a 90 en evitant les glissements.
									// Distance parcourue pendant cette boucle : A EVALUER
	{
		this->servoRight->write(pos);
		this->servoLeft->write(pos);
		delay(15);
	}
	
}
void Motor::turn(int angleDegree, int distanceMilliMeter)

// de 0° a 90° angle vers la droite du robot
//de 91° a 180° angel vers la gauche du robot
//
{
	if(angleDegree < 90 ) // angle vers la droite du robot
	{
		alpha = 90 - angleDegree;
		distanceRight = 15.97 * sqrt(1- cos(alpha) ) ;
		distanceLeft = ( distanceDroite * 308) / 127.58 ;
		
		
		for(pos=90 ; pos < 120; pos++)//Lancer les deux servo à 120 puis les arreter en différé pour gerer
									//le differentiel de distance a parcourir   ??? Bonne idée, ou pas, a voir
		{
			this->servoRight->write(pos);
			this->servoLeft->write(pos);
			delay(15);
		}
		
		// TODO : gérer le differentiel de distance entre les roues droites et gauches 
	}
	
	
}

