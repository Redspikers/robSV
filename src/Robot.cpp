/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Etat par défaut du robot : on cherche un CD
	this->state = Robot::SEARCH;

	//Construction de la map (codée en dur)
	this->map = new Map();

	//Algorithme de pathfinding
	this->pathfinding = new AStarLight(this->map, Robot::PLACE_RADIUS);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}


void Robot::setup() {
	
	
	attachInterrupt (2, incrementation_roueCodeuseRight(), RISING);
	attachInterrupt (5, incrementation_roueCodeuseLeft(), RISING);
}
void Robot::loop() {
	//TODO

	//Mettre à jour sa position

	//Mettre à jour la position de l'ennemi

	//Si SEARCH || BACK
		//Chercher son prochain déplacement (peut-être va t'on éviter de faire un appe lau pathfinding à chaque fois et faire du tampons
		//Vérifier le contenu de la prochaine case (un CD qui peut avoir été déplacé, où le robot adverse)
		//Se déplacer ou contourner
	//FinSi

	//Si TAKE
		//Amorcer le processus ou le continuer
	//FinSi

	//Si DROP
		//Amorcer le processus ou le continuer
	//FinSi

}
