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

class Robot {
	public:
		enum State {
		      SEARCH,
		      BACK,
		      TAKE,
		      DROP
		};
		static const int PLACE_RADIUS = 2;

		Robot();
		~Robot();

		//Fonctions à executer à chaque boucle de la Arduino, cette fonction prend les actions sur le moment et à venir
		void loop();
		void setup();

	private:
		State state;

		Map* map;
		AStarLight* pathfinding;

		//Bras
		//Déplacement
		//Reconnaissance
};

#endif /* ROBOT_H_ */
