#include "Arm.h"

Arm::Arm(int pinElbow, int pinShoulder, int pinPomp, int pinPushButton) {
	this->pinElbow = pinElbow;
	this->pinShoulder = pinShoulder;
	this->pinPushButton = pinPushButton;

	this->angleShoulderTake = Arm::ANGLE_SHOULDER_TAKE;
	this->angleElbowTake = Arm::ANGLE_ELBOW_TAKE;

	this->angleShoulderDrop = Arm::ANGLE_SHOULDER_DROP;
	this->angleElbowDrop = Arm::ANGLE_ELBOW_DROP;

	this->angleShoulderIdle = Arm::ANGLE_SHOULDER_IDLE;
	this->angleElbowIdle = Arm::ANGLE_ELBOW_IDLE;

	this->servoElbow = new Servo();
	this->servoShoulder = new Servo();
	this->pomp = new Pomp(pinPomp);

	this->servoElbow->attach(this->pinElbow);
	this->servoShoulder->attach(this->pinShoulder);


}

void Arm::takeCD() {
	/*
	 * On verifie qu'il est de bonne couleur et on attrape le cd
	 * Si à n'importe quel moment , le CD est laché (et donc le capteur ne voit plus rien)
	 * On retourne False
	 * On retourne True uniquement dans le cas où tout s'est bien passé 
	 * (bonne couleur & pas laché en cours & laché au dessus du tapis et retour position initiale
	 * */

	//Mouvement des deux servos. Le même tout le temps car on choppe que les CDs du bas
	this->servoElbow->write(this->angleShoulderTake); //Elbow
	this->servoShoulder->write(this->angleElbowTake); //Shoulder
	//FIN Mouvement

	//Compresion de la pomp
	this->pomp->compress();

	this->idle();
}

void Arm::dropInside() {
	//Mouvement des servos pour aller au tapis
	this->servoElbow->write(this->angleElbowDrop); //Elbow
	this->servoShoulder->write(this->angleShoulderDrop); //Shoulder
	//FIN Mouvement

	//Relachement au dessus du tapis
	this->pomp->drop();

	this->idle();
}

bool Arm::hasCD() {
	if(digitalRead(this->pinPushButton) == 1) {
		return true;
	}

	return false;
}

void Arm::idle() {
	//Retour position initiale
	this->servoElbow->write(this->angleElbowIdle); //Elbow
	this->servoShoulder->write(this->angleShoulderIdle); //Shoulder
	//FIN Mouvement
}
