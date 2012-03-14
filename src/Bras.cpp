#include "Bras.h"

#define ANGLE_EPAULE 30
#define ANGLE_COUDE 30

Bras::Bras() {
	this->servoCoude = new Servo();
	this->servoEpaule = new Servo();
	this->pompe = new Pompe();
	
	this->servoCoude()->attach(PIN_SERVO_COUDE);
	this->servoEpaule()->attach(PIN_SERVO_EPAULE);

}

bool Bras::attrapeCD() {
	/*
	 * On verifie qu'il est de bonne couleur et on attrape le cd
	 * Si à n'importe quel moment , le CD est laché (et donc le capteur ne voit plus rien)
	 * On retourne False
	 * On retourne True uniquement dans le cas où tout s'est bien passé 
	 * (bonne couleur & pas laché en cours & laché au dessus du tapis et retour position initiale
	 * */

	//Mouvement des deux servos. Le même tout le temps ?
	//~ this->servoCoude().
	
	
	
	//Compresion de la pompe 
	this->pompe->compresser();

	//Mouvement des servos pour aller au tapis

	//Relachement au dessus du tapis
	this->pompe->relacher();

	//Retour position initiale

	return true;
}

int Bras::getCapteurCouleur() {
	//return capteur.read(); ?
	return 0;
}

