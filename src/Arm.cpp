#include "Arm.h"

Arm::Arm() {
	this->servoElbow = new Servo();
	this->servoShoulder = new Servo();
	this->pomp = new Pomp();
	this->sensor = new SensorColor();

	this->servoElbow->attach(ELBOW);
	this->servoShoulder->attach(SHOULDER);

}

//A n'utiliser que avant le début du match. Inutile pendant le match
void Arm::idleBegin() {
	this->servoShoulder->write(ANGLE_SHOULDER_IDLE_BEGIN); //Shoulder
	this->servoElbow->write(ANGLE_ELBOW_IDLE_BEGIN); //Elbow
}

void Arm::exitIdleBegin() {
	this->move(ANGLE_SHOULDER_IDLE_BEGIN, ANGLE_SHOULDER_IDLE, true);
	this->move(ANGLE_ELBOW_IDLE_BEGIN, ANGLE_ELBOW_IDLE, false);
	//le bras se trouve alors en position "Idle"
}

void Arm::takeCD() {
	this->move(ANGLE_ELBOW_IDLE, ANGLE_ELBOW_TAKE, false);
	this->move(ANGLE_SHOULDER_IDLE, ANGLE_SHOULDER_TAKE, true);

	this->pomp->compress();

	delay(2500);

	this->idle();
}

void Arm::dropInside() {
	//Mouvement des servos pour aller au tapis
	
	this->move(ANGLE_ELBOW_IDLE, ANGLE_ELBOW_DROP, false);
	this->move(ANGLE_SHOULDER_IDLE, ANGLE_SHOULDER_DROP, true);

	//Relachement au dessus du tapis
	this->pomp->drop();

	this->idle();

}

bool Arm::seeCD() {
	if(this->sensor->isWhite()) {
		return true;
	}

	return false;
}

bool Arm::hasCD() {
	if(digitalRead(PUSH_CD) == 1) {
		return true;
	}

	return false;
}

void Arm::idle() {
	this->move(ANGLE_SHOULDER_DROP, ANGLE_SHOULDER_IDLE, true);
	this->move(ANGLE_ELBOW_DROP, ANGLE_ELBOW_IDLE, false);
}

void Arm::move(int angleBegin, int angleEnd, bool shoulder) {
	int i = 0;
	if(angleBegin < angleEnd) {
		if(shoulder) {
			for(i = angleBegin; i < angleEnd; i++) {
				this->servoShoulder->write(i);
				delay(15);
			}
		} else {
			for(i = angleBegin; i < angleEnd; i++) {
				this->servoElbow->write(i);
				delay(15);
			}
		}
	}

	else if(angleBegin > angleEnd) {
		if(shoulder) {
			for(i = angleBegin; i >= angleEnd; i--) {

				this->servoShoulder->write(i);
				delay(15);
			}
		} else {
			for(i = angleBegin; i >= angleEnd; i--) {
				this->servoElbow->write(i);
				delay(15);
			}
		}

	}
}

void Arm::stop() {
	this->pomp->drop();
}
