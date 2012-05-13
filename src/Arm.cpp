#include "Arm.h"

Arm::Arm() {
	this->servoElbow = new Servo();
	this->servoShoulder = new Servo();
	this->pomp = new Pomp();
	this->sensor = new SensorColor();

	this->servoElbow->attach(ELBOW);
	this->servoShoulder->attach(SHOULDER);

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
	this->servoElbow->write(ANGLE_ELBOW_TAKE); //Elbow
	this->servoShoulder->write(ANGLE_SHOULDER_TAKE); //Shoulder
	//FIN Mouvement

	//On vérifie qu'il y a bien un CD
	if(this->sensor->getColor() == SensorColor::WHITE) {
		//Compresion de la pompe
		this->pomp->compress();
	}

	//Dans tout les cas, on revient à la position initiale
	this->idle();
}

void Arm::dropInside() {
	//Mouvement des servos pour aller au tapis
	this->servoElbow->write(ANGLE_ELBOW_DROP); //Elbow
	this->servoShoulder->write(ANGLE_SHOULDER_DROP); //Shoulder
	//FIN Mouvement

	//Relachement au dessus du tapis
	this->pomp->drop();

	this->idle();
}

bool Arm::hasCD() {
	if(digitalRead(PUSH_CD) == 1) {
		return true;
	}

	return false;
}

void Arm::idle() {
	//Retour position initiale
	this->servoElbow->write(ANGLE_ELBOW_IDLE); //Elbow
	this->servoShoulder->write(ANGLE_SHOULDER_IDLE); //Shoulder
	//FIN Mouvement
}

void Arm::idleBegin() {
	this->servoElbow->write(ANGLE_ELBOW_IDLE); //Elbow
	this->servoShoulder->write(ANGLE_SHOULDER_IDLE); //Shoulder
	
}
