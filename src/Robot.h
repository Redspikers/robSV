/*
 * Robot.h
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>
#include "Map.h"
#include "AStarLight.h"
#include "Arm.h"
#include "Conveyor.h"
#include "Motor.h"

class Robot {
	public:
		enum State {
			IDLE,
			SEARCH,
			BACK,
			TAKE,
			DROP
		};
		static const int PLACE_RADIUS = 2;

		Robot();
		~Robot();

		//Fonctions de la arduino, reportées dans cette classe
		void setup();
		void loop();

		//Fonctions spécifiques à chaque états
		void actionIdle();
		void actionSearch();
		void actionBack();
		void actionTake();
		void actionDrop();


	private:
		//Etat du robot temps en temps réel (détermine le comportement)
		State state;

		//Carte
		Map* map;

		//Recherche de chemin (pathfinding)
		AStarLight* pathfinding;
		Node* path;

		//Bras
		Arm* arm;

		//Tapis
		Conveyor* conveyor;

		//Déplacement
		Motor* motor;

		//Reconnaissance (capteurs)
		Captor* captorBL;
		Captor* captorBM;
		Captor* captorBR;

		Captor* captorUL;
		Captor* captorUM;
		Captor* captorUR;

		Captor* captorBack;
};

#endif /* ROBOT_H_ */
