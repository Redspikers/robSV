/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Etat par défaut du robot : on cherche un CD
	this->state = Robot::State::IDLE;

	//Construction de la map (codée en dur)
	this->map = new Map();

	//Algorithme de pathfinding
	this->pathfinding = new AStarLight(this->map, Robot::PLACE_RADIUS);
}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}


void Robot::setup() {
	//TODO fix this error
	//attachInterrupt(2, this->motor->incrementation_roueCodeuseRight(), RISING);
	//attachInterrupt(5, this->motor->incrementation_roueCodeuseLeft(), RISING);

	//TODO indiquer la position de départ du robot, gauche ou droite
}
void Robot::loop() {
	//Selon l'état du robot, on adopte un comportement différent
	//L'ordre des états permet d'optimiser la boucle if/else (on limite les calculs de booléens)
	if(this->state == Robot::State::SEARCH) {
		this->actionSearch();
	} else if(this->state == Robot::State::BACK) {
		this->actionBack();
	} else if(this->state == Robot::State::TAKE) {
		this->actionTake();
	} else if(this->state == Robot::State::DROP) {
		this->actionDrop();
	} else if(this->state == Robot::State::IDLE) {
		this->actionIdle();
	}

}


void Robot::actionIdle() {
	//Seule chose à faire : tester le JACK
	//Si i la été retiré, alors on passe à l'état SEARCH
}
void Robot::actionSearch() {
	//Si un chemin existe (i.e. path non nul)
		//Mettre à jour les cases adjacentes via capteurs pour le robot adverse et/ou les CDs éventuels

		//Si c'était la fin du chemin
			//Si le CD est bien là
				//Passer en état TAKE
			//Sinon
				//Mettre à jour la carte, chercher un autre CD (nouveau chemin à faire)
			//FinSi
		//Sinon
			//Si pas de changements (le plus fréquent)
				//Se déplacer d'une case
			//Sinon si un CD est apparu
				//Passer en état TAKE
			//Sinon si le robot adverse est apparu
				//Recalculer un nouveau chemin (pour l'éviter)
		//FinSi
	//Sinon
		//Recherche le CD le plus proche
		//Calculer un chemin vers ce CD
	//FinSi
}
void Robot::actionBack() {
	//Si un chemin existe (i.e. path non nul)
		//Mettre à jour les cases adjacentes via capteurs pour le robot adverse et/ou les CDs éventuels

		//Si c'était la fin du chemin
			//Passer en état DROP
		//Sinon
			//Si pas de changements (le plus fréquent)
				//Se déplacer d'une case
			//Sinon si un CD est apparu
				//Rafraichir la carte avec ce nouveau CD
			//Sinon si le robot adverse est apparu
				//Recalculer un nouveau chemin (pour l'éviter)
		//FinSi
	//Sinon
		//Recherche de la zone où il faut déposer le CD
		//Calculer un chemin vers cette zone
	//FinSi
}
void Robot::actionTake() {
	//Se tourner vers le CDs
	//Le prendre
	//le mettre à l'intérieur
	//Si il y a moins de 4 CDs
		//On passe en état SEARCH
	//Sinon
		//Passer en état BACK
	//FinSi
}
void Robot::actionDrop() {
	//Se tourner
	//Lacher les CDs
	//Passer en état SEARCH
}
