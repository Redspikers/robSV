/*
 * Robot.h
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>
#include "Arm.h"
#include "Conveyor.h"
#include "Motor.h"
#include "Recognition.h"
#include "Pin.h"

#include "Position.h"

class Robot {
	public:
		enum Position {
			LEFT, RIGHT
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

	private:
		//Numéro du CD à aller attraper (22 au total)
		int targetCD;

		//Robot actif ou non ?
		bool active;

		int x;
		int y;
		int angle;

		//Bras
		Arm* arm;

		//Tapis
		Conveyor* conveyor;

		//Déplacement
		Motor* motor;

		//Reconnaissance (capteurs)
		Recognition* sensor;

		//Distance en MM
		void moveX(int newX);
		void moveY(int newY);
		//Tourne le robot en degré
		void turn(int newAngle);

		void take();
		void drop();

		void actionLeft();
		void actionRight();
};

#endif /* ROBOT_H_ */
