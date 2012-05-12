/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Le bras mécanique avec ventouse
	//this->arm = new Arm();

	//Le tapis au sein du robot
	this->conveyor = new Conveyor();

	//La motricité du robot (ses deux roues)
	this->motor = new Motor();

	//Les différents capteurs
	this->sensor = new Recognition();

	//Premier CD à attraper
	this->targetCD = 1;

	//Par défaut, le robot n'est pas actif
	this->active = false;

	if (START_POSITION == LEFT) {
		this->angle = START_LEFT_ANGLE;
		this->x = START_LEFT_X;
		this->y = START_LEFT_Y;
	} else if (START_POSITION == RIGHT) {
		this->angle = START_RIGHT_ANGLE;
		this->x = START_RIGHT_X;
		this->y = START_RIGHT_Y;
	}
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
		this->targetCD++;
	} else {
		if(digitalRead(JACK) == 1) {
			this->active = true;
		}
	}
}

void Robot::actionLeft() {
	switch (this->targetCD) {
		case 1:
			this->moveX(500 + ROBOT_HEIGHT + 100);

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
			this->moveY(1500);

			this->moveX(CD_PL_TM_X);
			this->moveY(CD_PL_TM_Y - ARM_REACH);

			this->turn(270);
			this->take();
			break;
		case 4:
			this->moveX(CD_PL_TL_X);
			this->moveY(CD_PL_TL_Y - ARM_REACH);

			this->turn(270);
			this->take();

			this->moveY(CAPTAIN_LEFT_Y);
			this->moveX(CAPTAIN_LEFT_X);

			this->drop();
			break;
		case 5:
			this->moveX(540);

			this->moveY(CD_PL_L_Y);
			this->moveX(CD_PL_L_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 6:
			this->moveY(CD_PL_BL_Y);
			this->moveX(CD_PL_BL_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 7:
			this->moveY(CD_PL_BM_Y);
			this->moveX(CD_PL_BM_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 8:
			this->moveY(640);

			this->moveX(CD_PL_BR_X);
			this->moveY(CD_PL_BR_Y - ARM_REACH);

			this->turn(90);
			this->take();

			this->moveX(650);

			this->moveY(STOCK_LEFT_Y);
			this->moveX(STOCK_LEFT_X);

			this->drop();
			break;
		case 9:
			this->moveX(750);

			this->moveY(CD_BL_Y);
			this->moveX(CD_BL_X - ARM_REACH);

			this->turn(180);
			this->take();
			break;
		case 10:
			this->moveY(CD_ML_Y);
			this->moveX(CD_ML_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 11:
			this->moveY(CD_MT_Y);
			this->moveX(CD_MT_X - ARM_REACH);

			this->turn(0);
			this->take();
			break;
		case 12:
			this->moveY(400);

			this->moveX(CD_MR_X);
			this->moveY(CD_MR_Y);

			this->turn(270);
			this->take();

			this->moveX(650);

			this->moveY(STOCK_LEFT_Y);
			this->moveX(STOCK_LEFT_X);

			this->drop();
			break;
		case 13:
			this->moveX(650);

			this->moveY(CD_MB_Y);
			this->moveX(CD_MB_X);

			this->turn(0);
			this->take();
			break;
		case 14:
			this->moveY(CD_BR_Y);
			this->moveX(CD_BR_X);

			this->turn(0);
			this->take();
			break;
		case 15:
			this->moveX(CD_PR_BL_X);
			this->moveY(CD_PR_BL_Y);

			this->turn(90);
			this->take();
			break;
		case 16:
			this->moveY(CD_PR_BM_Y);
			this->moveX(CD_PR_BM_X);

			this->turn(0);
			this->take();

			this->moveX(650);

			this->moveY(STOCK_LEFT_Y);
			this->moveX(STOCK_LEFT_X);

			this->drop();
			break;
		case 17:
			this->moveX(650);
			this->moveY(600);

			this->moveX(CD_PR_BR_X);
			this->moveY(CD_PR_BR_Y);

			this->turn(90);
			this->take();
			break;
		case 18:
			this->moveX(CD_PR_R_X);
			this->moveY(CD_PR_R_Y);

			this->turn(90);
			this->take();
			break;
		case 19:
			this->moveX(2400);

			this->moveY(CD_PR_TR_Y);
			this->moveX(CD_PR_TR_X);

			this->turn(180);
			this->take();
			break;
		case 20:
			this->moveY(CD_PR_TM_Y);
			this->moveX(CD_PR_TM_X);

			this->turn(180);
			this->take();

			this->moveX(2400);
			this->moveY(600);
			this->moveX(650);

			this->moveY(STOCK_LEFT_Y);
			this->moveX(STOCK_LEFT_X);

			this->drop();
			break;
		case 21:
			this->moveX(650);
			this->moveY(1500);

			this->moveX(CD_PR_TL_X);
			this->moveY(CD_PR_TL_Y);

			this->turn(270);
			this->take();
			break;
		case 22:
			this->moveY(CD_TR_Y);
			this->moveX(CD_TR_X);

			this->turn(0);
			this->take();

			this->moveX(650);
			this->moveY(STOCK_LEFT_Y);
			this->moveX(STOCK_LEFT_X);

			this->drop();
			break;

		default:
			this->actionEnd();
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
			this->actionEnd();
			break;
	}
}

void Robot::actionEnd() {
	//Lorsque le robot n'a plus rien à faire - il fait des tours
	this->motor->turn(180);
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

			this->x = newX;
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

			this->y = newY;
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

void Robot::take() {
	/*
	this->arm->takeCD();
	if (this->arm->hasCD()) {
		this->arm->dropInside();
	}
	*/
}

void Robot::drop() {
	/*
	//Se tourner - le cul vers la destination !
	if (START_POSITION == LEFT) {
		this->turn(0);
	} else {
		this->turn(180);
	}

	//Lacher les CDs
	this->conveyor->action();
	*/
}
