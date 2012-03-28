#include "Bras.h"

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

	//Mouvement des deux servos. Le même tout le temps car on choppe que les CDs du bas
	this->servoCoude-> write(ANGLE_COUDE1);//Coude
	this->servoEpaule->write(ANGLE_EPAULE1);//Epaule
	//FIN Mouvement
	
	if(getCapteurCouleur()){
		retourPositionInitiale();
		return false;
	}
	
	//Compresion de la pompe 
	this->pompe->compresser();

	//Mouvement des servos pour aller au tapis
	this->servoCoude-> write(ANGLE_COUDE2);//Coude
	this->servoEpaule->write(ANGLE_EPAULE2);//Epaule
	//FIN Mouvement

	//Relachement au dessus du tapis
	this->pompe->relacher();

	retourPositionInitiale();

	return true;
}

int Bras::getCapteurCouleur() {
	return analogRead(PIN_CAPTEUR_COULEUR);
}

void Bras::retourPositionInitiale(){
	//Retour position initiale
	this->servoCoude-> write(ANGLE_COUDE3);//Coude
	this->servoEpaule->write(ANGLE_EPAULE3);//Epaule
	//FIN Mouvement
}
