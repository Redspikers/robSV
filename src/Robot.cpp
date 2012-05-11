/*
 * Robot.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Robot.h"

Robot::Robot() {
	//Etat par défaut du robot : IDLE
	this->state = Robot::IDLE;

	//Construction de la map (codée en dur)
	this->map = new Map();

	//Algorithme de pathfinding
	this->pathfinding = new AStarLight(this->map);
	//Au lancement du robot, on a pas de chemin prédéterminé
	this->path = NULL;

	//Le bras mécanique avec ventouse
	this->arm = new Arm(Pin::ELBOW, Pin::SHOULDER, Pin::POMP, Pin::PUSH_CD, Pin::COLOR_SENSOR);

	//Le tapis au sein du robot
	this->conveyor = new Conveyor(Pin::CONVEYOR);

	//La motricité du robot (ses deux roues)
	this->motor = new Motor(Pin::MOTOR_LEFT, Pin::MOTOR_RIGHT);

	//Les différents capteurs
	this->sensor = new Recognition();

	this->cds = 0;

	//POSITION DE DEPART
	//Valeurs qui dépendent de la position de départ du robot, il suffit de changer la variable globales "POSITION"
	if(START_POSITION == LEFT){
		this->position = this->map->getCellWithDistance(155, 1750);
		//Angle de 0 on positionne le robot face à la carte, aligné sur l'axe des abcisses
		this->angle = 0;
		this->captainArea = this->map->getCaptainAreaLeft();
		this->stockArea = this->map->getStockAreaLeft();

	} else if(START_POSITION == RIGHT) {
		this->position = this->map->getCellWithDistance(2845, 1750);
		//Angle de 1800 on positionne le robot face à la carte (donc dans le sens inverse que LEFT), aligné sur l'axe des abcisses
		this->angle = 180;
		this->captainArea = this->map->getCaptainAreaRight();
		this->stockArea = this->map->getStockAreaRight();
	}

	//Par défaut, on a aucune cible, c'est l'algorithme qui se chargeras d'en trouver une dès que nécessaire
	this->target = NULL;

}

Robot::~Robot() {

}

void Robot::loop() {
	//Selon l'état du robot, on adopte un comportement différent
	//L'ordre des états permet d'optimiser la boucle if/else (on limite les calculs de booléens)
	if(this->state == SEARCH) {
		this->actionSearch();
	} else if(this->state == BACK) {
		this->actionBack();
	} else if(this->state == TAKE) {
		this->actionTake();
	} else if(this->state == DROP) {
		this->actionDrop();
	} else if(this->state == IDLE) {
		this->actionIdle();
	} else if(this->state == END) {
		this->actionEnd();
	}

}


void Robot::actionIdle() {
	//Si il a été retiré, alors on passe à l'état SEARCH
	if(digitalRead(Pin::JACK) == 1) {
		this->changeState(SEARCH);
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
			this->path = this->path->getNext();

			//Si c'était le dernier noeud, passer en état TAKE
			if(this->path != NULL) {
				this->move(this->path->getCell());
			} else {
				this->changeState(TAKE);
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
			this->path = this->path->getNext();

			//Si c'était le dernier noeud, passer en état TAKE
			if(this->path != NULL) {
				this->move(this->path->getCell());
			} else {
				this->changeState(DROP);
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
	this->turn(this->diffAngle(this->target));

	//Le prendre  ?(essayer partout ou le bouton poussoir)?
	this->arm->takeCD();

	//Le mettre à l'intérieur - si le CD a été pris
	if(this->arm->hasCD()) {
		this->arm->dropInside();
		this->cds = this->cds + 1;
		this->target->setCD(false);
	}

	this->target = NULL;

	//Si il y a moins de 4 CDs
	if(this->cds < Robot::MAX_CD) {
		//On passe en état SEARCH
		this->changeState(SEARCH);
	} else {
		//Passer en état BACK
		this->changeState(BACK);
	}
}

void Robot::actionDrop() {
	//Se tourner - le cul vers la destination !
	int angle = this->diffAngle(this->target) + 180;

	if(angle > 360) {
		angle = angle - 360;
	}
	this->turn(angle);

	//Lacher les CDs
	this->conveyor->action();

	//On incrémente le nombre de CD dans les zones correspondantes
	if(this->target == this->captainArea->getCenter()) {
		this->captainArea->addCD(this->cds);
	} else {
		this->stockArea->addCD(this->cds);
	}

	this->cds = 0;

	//Passer en état SEARCH
	this->changeState(SEARCH);
}
void Robot::actionEnd() {
	if(this->cds > 0) {
		//Si il reste des CDs à l'intérieur du robot, on va les déposer
		this->actionBack();
	} else {
		//Sinon il n'y a plus rien à faire

	}
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

int Robot::diffAngle(Cell* destination) {
	//ATTENTION : Dans cette fonction, on assume que les cellules sont carrées !
	int newAngle = 0;

	if(this->position->getX() < destination->getX()) {
		//Il faut se déplacer sur la droite
		newAngle = newAngle + 0;
	} else if(this->position->getX() > destination->getX()) {
		//Il faut se déplacer sur la gauche
		newAngle = newAngle + 180;
	} else {
		//On se déplace en ne changeant pas d'abcisse
	}

	if(this->position->getY() < destination->getY()) {
		//Il faut se déplacer vers le haut
		newAngle = newAngle + 90;
	} else if(this->position->getY() > destination->getY()) {
		//Il faut se déplacer vers le bas
		newAngle = newAngle - 90;
	} else {
		//On se déplace en ne changeant pas d'ordonnée
	}

	if(newAngle < 0) {
		newAngle = newAngle + 360;
	}

	return newAngle;
}

void Robot::move(Cell* destination) {
	//ATTENTION : Dans le déroulement de cette fonction on assume que la cellule destination est une des cellules voisines !

	//Premièrement, il faut déterminer l'angle que le robot doit avoir pour pouvoir avancer TOUT DROIT vers la cellule visée
	this->turn(this->diffAngle(destination));

	//Ensuite, il faut transcrire le changement de cellule en une distance en mm
	//Soit la case est une diagonale (X et Y diffèrent), soit non
	if(destination->getX() != this->position->getX() && destination->getY() != this->position->getY()) {
		this->motor->move(Map::CELL_DIAGONAL);
	} else if(destination->getX() != this->position->getX()) {
		this->motor->move(Map::CELL_WIDTH);
	} else if(destination->getY() != this->position->getY()) {
		this->motor->move(Map::CELL_HEIGHT);
	}

	this->position = destination;

}

void Robot::turn(int newAngle) {
	int diff = newAngle - this->angle;

	if(diff < 0) {
		diff = diff+360;
	}

	this->motor->turnOnSpot(diff);

	this->angle = newAngle;
}

void Robot::findPathToCD() {
	//Recherche le plus proche CD
	this->target = this->map->getClosestCD(this->position);

	//Si il n'y a plus de CD (pour X raisons, la principale étant que l'on a tous récupéré)
	if(this->target == NULL) {
		//Passer en état END
		this->changeState(END);
	} else {
		//Recherche des cellules où peut aller le robot (en tenant compte de sa corpulence et de sa portée du bras)
		Cell** possibleDestination = this->map->getStraights(this->target->getX(), this->target->getY(), PLACE_RADIUS);
		int countDestination = this->map->getStraightsCount(this->target->getX(), this->target->getY(), PLACE_RADIUS);
		Cell* destination = NULL;

		//Pour chaque cellule trouvées, on regarde si le robot peut y aller (ie, pas d'obstacles avec sa corpulence)
		for(int i = 0; (i < countDestination && destination==NULL) ; i++) {
			Cell** neighbors = this->map->getNeighbors(possibleDestination[i]->getX(), possibleDestination[i]->getY(), PLACE_RADIUS);
			int countNeighbors = this->map->getNeighborsCount(this->target->getX(), this->target->getY(), PLACE_RADIUS);
			bool blocked = false;
			for(int j=0 ; (j < countNeighbors && blocked==false) ; j++) {
				if(neighbors[j]->isBlocked()) {
					blocked = true;
				}
			}

			if(!blocked) {
				destination = possibleDestination[i];
			}
		}


		//On calcule le chemin intégral ver le CD, ce chemni est calculé sans tenir compte de la taille du robot
		this->path = this->pathfinding->compute(this->position, destination, PLACE_RADIUS);

		//TODO Mémoire leak sur ceux qui restent ?
	}
}

void Robot::findPathToBack() {
	//Recherche de la zone où il faut déposer
	if(this->captainArea->countCD() < 4) {
		this->target = this->captainArea->getCenter();
	} else {
		this->target = this->stockArea->getCenter();
	}

	//Recherche des cellules où peut aller le robot (en tenant compte de sa corpulence et de sa portée du bras)
	Cell** possibleDestination = this->map->getStraights(this->target->getX(), this->target->getY(), PLACE_RADIUS);
	int countDestination = this->map->getStraightsCount(this->target->getX(), this->target->getY(), PLACE_RADIUS);
	Cell* destination = NULL;

	//Pour chaque cellule trouvées, on regarde si le robot peut y aller (ie, pas d'obstacles avec sa corpulence)
	for(int i = 0; (i < countDestination && destination==NULL) ; i++) {
		Cell** neighbors = this->map->getNeighbors(possibleDestination[i]->getX(), possibleDestination[i]->getY(), PLACE_RADIUS);
		int countNeighbors = this->map->getNeighborsCount(this->target->getX(), this->target->getY(), PLACE_RADIUS);
		bool blocked = false;
		for(int j=0 ; (j < countNeighbors && blocked==false) ; j++) {
			if(neighbors[j]->isBlocked()) {
				blocked = true;
			}
		}

		if(!blocked) {
			destination = possibleDestination[i];
		}
	}


	//On calcule le chemin intégral ver le CD, ce chemni est calculé sans tenir compte de la taille du robot
	this->path = this->pathfinding->compute(this->position, destination, PLACE_RADIUS);

	//TODO Mémoire leak sur ceux qui restent ?
}

Motor* Robot::getMotor() {
	return this->motor;
}
