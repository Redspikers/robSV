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
#include "Gate.h"
#include "Conveyor.h"
#include "Motor.h"
#include "Timer.h"
#include "Recognition.h"
#include "Pin.h"
#include "Definition.h"

class Robot {
	public:
		//Left = Violet ; Right = Rouge ; None = none (ET OUI)
		enum Position {
			LEFT, RIGHT, NONE
		};

		enum Action {
			BEGIN, SEARCH, TAKE, DROP, DUMB, HOMOLOGATION
		};

		//Passe t'on l'homologation ? ROFL
		static const bool HAS_HOMOLOGATION = false;
		/*
		 *
		 */

		Robot();
		~Robot();

		//Fonctions de la arduino, reportées dans cette classe
		void loop();
		Motor* getMotor();
		Recognition* getRecognition();
		void stop();

		void init();

	private:
		Robot::Position position;

		//Robot actif ou non ?
		bool active;
		bool fistLoop;

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

		//Porte
		Gate* gate;

		//Déplacement
		Motor* motor;

		//Reconnaissance (capteurs)
		Recognition* sensor;

		Timer* timer;

		//Distance en MM
		bool move(int newX, int newY, bool searchCD);
		//Tourne le robot en degré
		void turn(int newAngle);
		bool take();
		void drop();
		void canonicalMove(int distance);

		void actionBegin();
		void actionSearch();
		void actionTake();
		void actionDrop();
		void actionDumb();
		void actionHomologation();

		void correctAngle();

		bool avoid();
};

#endif /* ROBOT_H_ */
