/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Etat par défaut du robot : IDLE
	this->state = Robot::State::IDLE;

	//Construction de la map (codée en dur)
	this->map = new Map();

	//Algorithme de pathfinding
	this->pathfinding = new AStarLight(this->map, Robot::PLACE_RADIUS);
	//Au lancement du robot, on a pas de chemin prédéterminé
	this->path = NULL;

	//Le bras mécanique avec ventouse
	this->arm = new Arm(Pin::ELBOW, Pin::SHOULDER, Pin::POMP);

	//Le tapis au sein du robot
	this->conveyor = new Conveyor(Pin::CONVEYOR);

	//La motricité du robot (ses deux roues)
	this->motor = new Motor(Pin::MOTOR_LEFT, Pin::MOTOR_RIGHT);

	//Les différents capteurs
	this->captorBL = new Captor(Pin::CAPTOR_BOTTOM_LEFT);
	this->captorBM = new Captor(Pin::CAPTOR_BOTTOM_MIDDLE);
	this->captorBR = new Captor(Pin::CAPTOR_BOTTOM_RIGHT);

	this->captorTL = new Captor(Pin::CAPTOR_TOP_LEFT);
	this->captorTM = new Captor(Pin::CAPTOR_TOP_MIDDLE);
	this->captorTR = new Captor(Pin::CAPTOR_TOP_RIGHT);

	this->captorBack = new Captor(Pin::CAPTOR_BACK);

	this->cds = 0;

	//Valeurs qui dépendent de la position de départ du robot, il suffit de changer la variable globales "POSITION"
	if(START_POSITION == Position::LEFT){
		//TODO régler les valeurs
		this->position = this->map->getCell(0, 0);
		this->angle = 0;
	} else if(START_POSITION == Position::RIGHT) {
		//TODO régler les valeurs
		this->position = this->map->getCell(0, 0);
		this->angle = 0;
	}

	this->target = NULL;

}

Robot::~Robot() {

}


void Robot::setup() {
	//TODO fix this error - peut-être le mettre dans la fonction setup ?
	//attachInterrupt(2, this->motor->incrementation_roueCodeuseRight(), RISING);
	//attachInterrupt(5, this->motor->incrementation_roueCodeuseLeft(), RISING);
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
	//TODO

	//Si il a été retiré, alors on passe à l'état SEARCH
	if() {
		this->changeState(Robot::State::SEARCH);
	}
}

void Robot::actionSearch() {
	//Mettre à jour les cases adjacentes via capteurs pour le robot adverse et/ou les CDs éventuels
	bool updated = this->updateMap();

	//Si un chemin existe (i.e. path non nul)
	if(this->hasPath()) {
		//Si pas de changements (le plus fréquent)
		if(!updated) {
			//Se déplacer d'une case
			this->move(this->path->getCell());

			this->path = this->path->getNext();
			//Si c'était le dernier noeud, passer en état TAKE
			if(this->path == NULL) {
				this->changeState(Robot::State::TAKE);
			}
		} else {
			this->findPathToCD();
		}
	} else {
		this->findPathToCD();
	}
}

void Robot::actionBack() {
	//Mettre à jour les cases adjacentes via capteurs pour le robot adverse et/ou les CDs éventuels
	bool updated = this->updateMap();

	//Si un chemin existe (i.e. path non nul)
	if(this->hasPath()) {
		//Si pas de changements (le plus fréquent)
		if(!updated) {
			//Se déplacer d'une case
			this->move(this->path->getCell());

			this->path = this->path->getNext();
			//Si c'était le dernier noeud, passer en état DROP
			if(this->path == NULL) {
				this->changeState(Robot::State::DROP);
			}
		} else {
			this->findPathToBack();
		}

	} else {
		this->findPathToBack();
	}
}

void Robot::actionTake() {
	//Se tourner vers le CDs
	//TODO

	//Le prendre (essayer partout ou le bouton poussoir)
	//TODO

	//Le mettre à l'intérieur
	//TODO

	//Si il y a moins de 4 CDs
	if(this->cds < Robot::MAX_CD) {
		//On passe en état SEARCH
		this->changeState(Robot::State::SEARCH);
	} else {
		//Passer en état BACK
		this->changeState(Robot::State::BACK);
	}
}

void Robot::actionDrop() {
	//Se tourner
	//TODO

	//Lacher les CDs
	//TODO

	//Passer en état SEARCH
	this->changeState(Robot::State::SEARCH);
}

void Robot::changeState(Robot::State newState) {
	this->state = newState;
}

bool Robot::hasPath() {
	if(this->path != NULL) {
		return true;
	}
	return false;
}

bool Robot::updateMap() {
	bool result = false;

	//TODO Mettre à jour la carte avec les capteurs

	return result;
}

void Robot::move(Cell* destination) {
	//TODO - utiliser le motor (simple) mettre à jour l'angle et tourner éventuellement le robot
}

void Robot::findPathToCD() {
	//Recherche le plus proche CD (car la carte a été mis à jour)
	//TODO - prendre en compte le fait qu'il y a 3 cases de différence entre le robot et le cd (PLACE_RADIUS+1)
	//this->target = this->map->getClosestCD(this->position);
	//Recalculer un nouveau chemin (pour l'éviter)
}

void Robot::findPathToBack() {
	//Recherche de la zone où il faut déposer
	//TODO
	//TODO - prendre en compte le fait qu'il y a 2 cases de différence (PLACE_RADIUS)
}
