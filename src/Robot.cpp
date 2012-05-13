/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Le bras mécanique avec ventouse
	this->arm = new Arm();

	//Le tapis au sein du robot
	this->conveyor = new Conveyor();

	//La motricité du robot (ses deux roues)
	this->motor = new Motor();

	//Les différents capteurs
	this->sensor = new Recognition();

	this->active = true;

	if(START_POSITION == LEFT) {
		this->angle = START_LEFT_ANGLE;
		this->x = START_LEFT_X;
		this->y = START_LEFT_Y;
	} else if(START_POSITION == RIGHT) {
		this->angle = START_RIGHT_ANGLE;
		this->x = START_RIGHT_X;
		this->y = START_RIGHT_Y;
	}

	//Action par défaut (lorsque le robot sera actif)
	this->action = BEGIN;

	this->cdInside = 0;
	this->cdDrop = 0;

}

Robot::~Robot() {

}

void Robot::loop() {
	if(this->active) {
		if(this->action == SEARCH) {
			this->actionSearch();
		} else if(this->action == TAKE) {
			this->actionTake();
		} else if(this->action == DROP) {
			this->actionDrop();
		} else if(this->action == BEGIN) {
			this->actionBegin();
		}
	} else {
		//Le robot s'arrête, on ne fait plus rien
	}
}

void Robot::actionBegin() {
	if(digitalRead(JACK) == 1) {
		//On attend que le petit robot bouge
		delay(2000);

		//On avance assez pour sortir de la zone du capitaine
		if(START_POSITION == LEFT) {
			this->move(this->x + 800, this->y);
		} else if(START_POSITION == RIGHT) {
			this->move(this->x - 800, this->y);
		}

		//On passe en état SEARCH pour la prochaine boucle
		this->action = SEARCH;
	}
}

void Robot::actionSearch() {

}

void Robot::actionTake() {

}

void Robot::actionDrop() {
	if(this->cdDrop < MAX_CAPTAIN_CD) {
		//Se tourner vers le mur du haut
		this->turn(90);

		//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 400mm)
		while(!this->sensor->isWall()) {
			this->move(this->x, this->y + 400);
		}

		//Corriger l'écart entre l'angle réel et l'angle en mémoire
		this->correctAngle();

		//Se déplacer à gauche ou droite (selon la position de départ)
		if(START_POSITION == LEFT) {
			//On se tourne vers la zone du capitaine
			this->turn(180);

			//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 400mm)
			while(!this->sensor->isWall()) {
				this->move(this->x + 100, this->y);
			}

			this->drop();

			//On sort de la zone
			this->move(this->x + 800, this->y);

		} else if(START_POSITION == RIGHT) {
			//On se tourne vers la zone du capitaine
			this->turn(0);

			//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 400mm)
			while(!this->sensor->isWall()) {
				this->move(this->x + 100, this->y);
			}

			this->drop();

			//On sort de la zone
			this->move(this->x - 800, this->y);
		}

	} else {
		//TODO - Aller vers la zone de stock
	}
}

void Robot::correctAngle() {
	int side = 0;
	int startAngle = this->angle;

	//On calcule la distance théorique que doit avoir le robot
	side = this->sensor->getDistanceBM() / (cos(ANGLE_BETWEEN_CAPTOR));

	while(!this->sensor->isWallParallel()) {
		//On compare cette distance théorique avec la réelle
		if(side < this->sensor->getDistanceBL()) {
			//On doit tourner le robot vers la droite (on le fait par pas de 1 degrée)
			this->turn(this->angle - 1);
		} else {
			//On doit tourner le robot vers la gauche (on le fait par pas de 1 degrée)
			this->turn(this->angle + 1);
		}
	}

	this->angle = startAngle;
}

void Robot::move(int newX, int newY) {
	//Calculer la distance et l'angle
	int distance = sqrt((newX - this->x) * (newX - this->x) + (newY - this->y) * (newY - this->y));
	int angle = tan(abs(newY - this->y) / abs(newX - this->x));

	angle = degrees(angle);

	this->turn(angle);

	//TODO faire des petits mouvements et vérifier les obstacles !

	this->motor->move(distance);

	this->x = newX;
	this->y = newY;
}

void Robot::turn(int newAngle) {
	int diff = newAngle - this->angle;

	while(diff < 0) {
		diff = diff + 360;
	}
	while(diff >= 360) {
		diff = diff - 360;
	}

	this->motor->turn(diff);

	this->angle = newAngle;
}

Motor* Robot::getMotor() {
	return this->motor;
}

Recognition* Robot::getRecognition() {
	return this->sensor;
}

void Robot::take() {
	this->arm->takeCD();
	 if (this->arm->hasCD()) {
	 this->arm->dropInside();
	 }

}

void Robot::drop() {
	//Se tourner - le cul vers la destination !
	if(START_POSITION == LEFT) {
		this->turn(0);
	} else if(START_POSITION == RIGHT) {
		this->turn(180);
	}

	//Lacher les CDs
	 this->conveyor->action();

	 this->cdDrop = this->cdDrop + this->cdInside;

	 this->cdInside = 0;

}

void Robot::setInactive() {
	this->active = false;
}
