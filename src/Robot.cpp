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
	this->motor = new Motor(MOTOR_LEFT, MOTOR_RIGHT);

	//Les différents capteurs
	this->sensor = new Recognition();

	//Premier CD à attraper
	this->targetCD = 1;

	//Par défaut, le robot n'est pas actif
	this->active = false;
}

Robot::~Robot() {

}

void Robot::loop() {
	if (this->active) {
		if (START_POSITION == LEFT) {
			this->actionLeft();
		} else if (START_POSITION == RIGHT) {
			this->actionRight();
		}
	} else {
		if(digitalRead(JACK) == 1) {
			this->active = true;
		}
	}
}

void Robot::actionLeft() {
	switch (this->targetCD) {
		case 1:
			this->moveX(510);

			this->moveY(CD_TL_Y);
			this->moveX(CD_TL_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 2:
			this->moveX(CD_PL_TR_X);
			this->moveY(CD_PL_TR_Y - ARM_REACH);

			this->turn(270);
			this->take();
			break;
		case 3:
			this->move(CD_PL_TM_X, CD_PL_TM_Y, false);
			this->turn(180);
			this->take();
			break;
		case 4:
			this->move(CD_PL_TL_X, CD_PL_TL_Y, true);
			this->turn(270);
			this->take();

			this->move(CAPTAIN_LEFT_X, CAPTAIN_LEFT_Y, false);
			this->drop();
			break;
		case 5:
			this->move(CD_PL_L_X, CD_PL_L_Y, true);
			this->turn(270);
			this->take();
			break;
		case 6:
			this->move(CD_PL_BL_X, CD_PL_BL_Y, false);
			this->turn(0);
			this->take();
			break;
		case 7:
			this->move(CD_PL_BM_X, CD_PL_BM_Y, false);
			this->turn(0);
			this->take();
			break;
		case 8:
			this->move(CD_PL_BR_X, CD_PL_BR_Y, true);
			this->turn(0);
			this->take();

			this->move(STOCK_LEFT_X, STOCK_LEFT_Y, true);
			this->drop();
			break;
		case 9:
			this->move(CD_BL_X, CD_BL_Y, true);
			this->turn(180);
			this->take();
			break;

		case 10:
			this->move(CD_ML_X, CD_ML_Y, true);
			this->turn(0);
			this->take();
			break;
		case 11:
			this->move(CD_MT_X, CD_MT_Y, false);
			this->turn(0);
			this->take();
			break;
		case 12:
			this->move(CD_MR_X, CD_MR_Y, true);
			this->turn(270);
			this->take();

			this->move(STOCK_LEFT_X, STOCK_LEFT_Y,);
			this->drop();
			break;
		case 13:
			this->move(CD_MB_X, CD_MB_Y);
			this->turn(270);
			this->take();
			break;
		case 14:
			this->move(CD_BR_X, CD_BR_Y);
			this->turn(270);
			this->take();
			break;
		case 15:
			this->move(CD_PR_BL_X, CD_PR_BL_Y);
			this->turn(270);
			this->take();
			break;
		case 16:
			this->move(CD_PR_BM_X, CD_PR_BM_Y);
			this->turn(270);
			this->take();

			this->move(STOCK_LEFT_X, STOCK_LEFT_Y);
			this->drop();
			break;
		case 17:
			this->move(CD_PR_BR_X, CD_PR_BR_Y);
			this->turn(270);
			this->take();
			break;
		case 18:
			this->move(CD_PR_R_X, CD_PR_R_Y);
			this->turn(270);
			this->take();
			break;
		case 19:
			this->move(CD_PR_TR_X, CD_PR_TR_Y);
			this->turn(270);
			this->take();
			break;
		case 20:
			this->move(CD_PR_TM_X, CD_PR_TM_Y);
			this->turn(270);
			this->take();

			this->move(STOCK_LEFT_X, STOCK_LEFT_Y);
			this->drop();
			break;
		case 21:
			this->move(CD_PR_TL_X, CD_PR_TL_Y);
			this->turn(270);
			this->take();
			break;
		case 22:
			this->move(CD_TR_X, CD_TR_Y);
			this->turn(270);
			this->take();

			this->move(STOCK_LEFT_X, STOCK_LEFT_Y);
			this->drop();
			break;

		default:
			this->active = false;
			break;
	}
}

void Robot::actionRight() {
	switch (this->targetCD) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;
		case 12:

			break;
		case 13:

			break;
		case 14:

			break;
		case 15:

			break;
		case 16:

			break;
		case 17:

			break;
		case 18:

			break;
		case 19:

			break;
		case 20:

			break;
		case 21:

			break;
		case 22:

			break;

		default:
			this->active = false;
			break;
	}
}

void Robot::moveX(int newX) {
	//On se déplace en X
		if (this->x != newX) {
			if (this->x < newX) {
				this->turn(0);
				this->motor->move(newX - this->x);
			} else {
				this->turn(180);
				this->motor->move(this->x - newX);
			}
		}
}
void Robot::moveY(int newY) {
	//On se déplace en Y
		if(this->y != newY) {
			if (this->y < newY) {
				this->turn(90);
				this->motor->move(newY - this->y);
			} else {
				this->turn(270);
				this->motor->move(this->y - newY);
			}
		}
}

void Robot::turn(int newAngle) {
	int diff = newAngle - this->angle;

	if (diff < 0) {
		diff = diff + 360;
	}

	this->motor->turnOnSpot(diff);

	this->angle = newAngle;
}

Motor* Robot::getMotor() {
	return this->motor;
}

void Robot::take() {
	this->arm->takeCD();
	if (this->arm->hasCD()) {
		this->arm->dropInside();
	}
}

void Robot::drop() {
	//Se tourner - le cul vers la destination !
	if (START_POSITION == LEFT) {
		this->turn(0);
	} else {
		this->turn(180);
	}

	//Lacher les CDs
	this->conveyor->action();
}
