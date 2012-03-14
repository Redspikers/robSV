#include "Bras.h"

//Temps d'éxecution des moteurs pour le mouvement 1 (Chopper le CD)
#define TEMPS_EPAULE1    30
#define TEMPS_COUDE1     20
//Temps d'éxecution des moteurs pour le mouvement 2 (Amener au tapis)
#define TEMPS_EPAULE2    30
#define TEMPS_COUDE2     20
//Temps d'éxecution des moteurs pour le mouvement 3 (Retour position initiale)
#define TEMPS_EPAULE3    30
#define TEMPS_COUDE3     20

#define VITESSE_MOTEUR  40 //Vitesse de rotation du moteur

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
	//Coude
	this->servoCoude-> write(90+VITESSE_MOTEUR);
	delay(TEMPS_COUDE1);
	this->servoCoude-> write(90);
	
	//Epaule
	this->servoEpaule->write(90+VITESSE_MOTEUR);
	delay(TEMPS_EPAULE1);
	this->servoEpaule->write(90);
	//FIN Mouvement
	
	//~ if(getCapteurCouleur())
		//~ return False;
	
	//Compresion de la pompe 
	this->pompe->compresser();

	//Mouvement des servos pour aller au tapis
	//Coude
	this->servoCoude-> write(90+VITESSE_MOTEUR);
	delay(TEMPS_COUDE2);
	this->servoCoude-> write(90);
	
	//Epaule
	this->servoEpaule->write(90+VITESSE_MOTEUR);
	delay(TEMPS_EPAULE2);
	this->servoEpaule->write(90);
	//FIN Mouvement

	//Relachement au dessus du tapis
	this->pompe->relacher();

	//Retour position initiale
	//Coude
	this->servoCoude-> write(90-VITESSE_MOTEUR);
	delay(TEMPS_COUDE1);
	this->servoCoude-> write(90);
	
	//Epaule
	this->servoEpaule->write(90-VITESSE_MOTEUR);
	delay(TEMPS_EPAULE1);
	this->servoEpaule->write(90);
	//FIN Mouvement

	return true;
}

int Bras::getCapteurCouleur() {
	return analogRead(PIN_CAPTEUR_COULEUR);
}

