/*
 * Robot.h
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>
#include <math.h>

#include "Arm.h"
#include "Conveyor.h"
#include "Motor.h"
#include "Recognition.h"
#include "Pin.h"

#include "Position.h"

#define MAX_INSIDE_CD 4
#define MAX_CAPTAIN_CD 4

class Robot {
	public:
		enum Position {
			LEFT, RIGHT
		};

		enum Action {
			BEGIN, SEARCH, TAKE, DROP
		};

		/**
		 * Variables de configuration
		 */
		//Position de départ du robot - Qualifie les zones et la cellule de départ pour le robot
		static const Robot::Position START_POSITION = Robot::LEFT;
		/*
		 *
		 */

		Robot();
		~Robot();

		//Fonctions de la arduino, reportées dans cette classe
		void loop();
		Motor* getMotor();
		void setInactive();

	private:
		//Robot actif ou non ?
		bool active;

		Action action;

		//Ces valeurs ne sont pas exactes, et le robot le sait !
		int x;
		int y;
		int angle;

		int cdInside;

		int cdDrop;

		//Bras
		Arm* arm;

		//Tapis
		Conveyor* conveyor;

		//Déplacement
		Motor* motor;

		//Reconnaissance (capteurs)
		Recognition* sensor;


		//Distance en MM
		void move(int newX, int newY);
		//Tourne le robot en degré
		void turn(int newAngle);
		void take();
		void drop();

		void actionBegin();
		void actionSearch();
		void actionTake();


		void actionDrop();
		void correctAngle();
};

#endif /* ROBOT_H_ */
