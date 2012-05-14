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

	//Lancement du timer qui permet l'arret du robot au bout de 85 secondes
	Timer3.initialize(85000000);
	//Timer3.pwm(13, 512); Supprimer si l'arret marche
	Timer3.attachInterrupt(this->stop);

	this->active = true;
	this->cdInside = 0;
	this->cdDrop = 0;

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
		delay(DELAY_BEFORE_BEGIN);

		//On avance assez pour sortir de la zone du capitaine
		this->canonicalMove(800);

		//On passe en état SEARCH pour la prochaine boucle
		this->action = SEARCH;
	}
}

void Robot::actionSearch() {
	bool cdFound = false;
	//Le robot va faire des tours de la carte à la recherche de CD, comme à Disney Land mais en mieux et plus hasardeux.
	if((this->x <= MAP_WIDTH / 2) && (this->y <= MAP_HEIGHT / 2)) {
		cdFound = this->move(2200, 300, true);
	} else if((this->x <= MAP_WIDTH / 2) && (this->y >= MAP_HEIGHT / 2)) {
		cdFound = this->move(800, 300, true);
	} else if((this->x >= MAP_WIDTH / 2) && (this->y <= MAP_HEIGHT / 2)) {
		cdFound = this->move(2200, 1700, true);
	} else if((this->x >= MAP_WIDTH / 2) && (this->y >= MAP_HEIGHT / 2)) {
		cdFound = this->move(800, 1700, true);
	}

	if(cdFound) {
		this->action = TAKE;
	}

	//A noter qu'à la fin d'un tour, il va aller corriger son angle (car au dela de 4 virages la précision devrait se faire ressentir)
	//TODO
}

void Robot::actionTake() {

}

void Robot::actionDrop() {
	if(this->cdDrop < MAX_CAPTAIN_CD) {
		//Se tourner vers le mur du haut
		this->turn(90);

		//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 100mm)
		while(!this->sensor->isWall()) {
			this->move(this->x, this->y + 100, false);
		}

		//Corriger l'écart entre l'angle réel et l'angle en mémoire
		this->correctAngle();

		//Se déplacer à gauche ou droite (selon la position de départ)
		if(START_POSITION == LEFT) {
			//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 100mm)
			while(!this->sensor->isWall()) {
				this->move(this->x - 100, this->y, false);
			}

			this->drop();

			//On sort de la zone
			this->move(this->x + 800, this->y, false);

		} else if(START_POSITION == RIGHT) {
			//Se déplacer tant que les 3 capteurs du bas n'ont pas vu de mur (on se déplace par pas de 100mm)
			while(!this->sensor->isWall()) {
				this->move(this->x + 100, this->y, false);
			}

			this->drop();

			//On sort de la zone
			this->move(this->x - 800, this->y, false);
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

bool Robot::move(int newX, int newY, bool searchCD) {
	//Calculer la distance et l'angle
	int distance = sqrt((newX - this->x) * (newX - this->x) + (newY - this->y) * (newY - this->y));
	int angle = 0;
	int distanceLeft = distance;

	if(this->x == newX) {
		if(this->y < newY) {
			angle = 90;
		} else if(this->y > newY) {
			angle = 270;
		} else if(this->y == newY) {
			angle = 0;
		}
	} else {
		angle = atan(fabs(newY - this->y) / fabs(newX - this->x));
		angle = degrees(angle);

		if(this->x < newX) {
			if(this->y < newY) {

			} else if(this->y > newY) {
				angle = 270 + angle;
			} else {
				angle = 0;
			}
		} else if(this->x > newX) {
			if(this->y < newY) {
				angle = 90 + angle;
			} else if(this->y > newY) {
				angle = 180 + angle;
			} else {
				angle = 180;
			}
		}
	}

	this->turn(angle);

	//La boucle while ne s'arrête que lorsque newX et newY (destination finale) ont été atteint
	while(distanceLeft > 0) {
		//Si un CD est visible et que 'searchCD' est sur TRUE, alors on quitte la fonction en renvoyant true
		if(this->sensor->isCD() && searchCD) {
			return true;
		}

		//Si il y a un quelconque obstacle, entammer une procédure d'évitemment (boucle if)
		if(this->sensor->isObstacle() || this->sensor->isRobot()) {
			//Tant que les capteurs repèrent l'obstacle
			while(this->sensor->isObstacle() || this->sensor->isRobot()) {
				//Le robot se tourne petit à petit
				this->turn(this->angle + 1);
			}
			//Lorsque l'obstacle n'est plus visible, on avance de 100mm
			this->canonicalMove(100);

			//On met à jour la distance et l'angle car la procédure d'évitemment à probablement modifier l'angle de robot et donc sa distance par rapport à son objectif initial
			angle = tan(abs(newY - this->y) / abs(newX - this->x));
			distance = sqrt((newX - this->x) * (newX - this->x) + (newY - this->y) * (newY - this->y));
			distanceLeft = distance;

			//On tourne le robot à nouveau vers sa destination
			this->turn(angle);
		}

		//On avance par pas de 100mm tant que l'on est pas arrivé
		if(distanceLeft > 100) {
			this->canonicalMove(100);
			distanceLeft = distanceLeft - 100;
		} else {
			this->canonicalMove(distanceLeft);
			distanceLeft = 0;
		}

	}

	//Si on arrive à cette doncition, c'est que le chemin est terminé, on renvoit donc false si on cherche des CDs et true le cas contraire
	if(searchCD) {
		return false;
	}

	return true;
}

void Robot::canonicalMove(int distance) {
	this->motor->move(distance);

	if(cos(this->angle) != 0) {
		this->x = this->x + (distance / cos(this->angle));
	}
	if(sin(this->angle) != 0) {
		this->y = this->y + (distance / sin(this->angle));
	}
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
	//TODO
	/*
	 this->arm->takeCD();
	 if (this->arm->hasCD()) {
	 this->arm->dropInside();
	 }
	 */

}

void Robot::drop() {
	//Se tourner - le cul vers la destination !
	if(START_POSITION == LEFT) {
		this->turn(0);
	} else if(START_POSITION == RIGHT) {
		this->turn(180);
	}

	//TODO
	/*
	 //Lacher les CDs
	 this->conveyor->action();
	 */
	this->cdDrop = this->cdDrop + this->cdInside;

	this->cdInside = 0;

}

void Robot::setInactive() {
	this->active = false;
}

/***************MARSUPILAMI MODIF APPORTER PAR RAPPORT A Robot.cpp ********/
/***** DECLARATION DES METHODE A AJOUTER DANS Robot.h ****/

void Robot::frontCD() {

//le CD est en face !
	if(this->sensor->getDistanceBM() <= DISTANCE_CD_TAKE) {

		this->motor->move(this->sensor->getDistanceBM());
		if(this->sensor->isCDInFront()) {
			return; // Pret pour take
		}

		else if(this->sensor->getDistanceBM() != 0 && this->sensor->getDistanceBM() < DISTANCE_CD_TAKE) {
			this->motor->move(this->sensor->getDistanceBM());
			return; //On est pret pour take
		} else {
			//TODO Robot plus en face du CD, s'est perdu
		}

	} else if(this->sensor->getDistanceBL() <= DISTANCE_CD_TAKE) {

		this->motor->turn(ANGLE_BETWEEN_CAPTOR);
		if(this->sensor->getDistanceBM() <= DISTANCE_CD_TAKE) { //le virage a été bon
			this->motor->move(this->sensor->getDistanceBM());
			if(this->sensor->isCDInFront()) {
				return; // On est pret pour take
			} else if(this->sensor->getDistanceBM() != 0 && this->sensor->getDistanceBM() <= DISTANCE_CD_TAKE) {
				this->motor->move(this->sensor->getDistanceBM());
				return; // On est pret pour take
			} else { //move mauvais
					 //TODO robot plus en face du CD
			}

		} else { //virage mauvais
				 //TODO robot pas en face du CD
		}

	} else if(this->sensor->getDistanceBR() <= DISTANCE_CD_TAKE) {

		this->motor->turn(360 - ANGLE_BETWEEN_CAPTOR);
		if(this->sensor->getDistanceBM() <= DISTANCE_CD_TAKE) { //le virage a été bon
			this->motor->move(this->sensor->getDistanceBM());
			if(this->sensor->isCDInFront()) {
				return; // On est pret pour take
			} else if(this->sensor->getDistanceBM() != 0 && this->sensor->getDistanceBM() <= DISTANCE_CD_TAKE) {
				this->motor->move(this->sensor->getDistanceBM());
				return; // on est pret pour take
			} else { //move mauvais
					 //TODO robot plus en face du CD
			}

		} else { //turn mauvais
				 //TODO robot pas en face du CD
		}

	}
}

/**** FIN DE MODIF *****/

void Robot::stop() {
//Arret des moteurs
this->motor->stop();

//Arret du tapis
this->conveyor->stop();

//Arret du bras (=relachement de la pompe)
this->arm->stop();
//On met le programme en pause une heure = on bloque l'execution du programme
delay(3600000);




}
