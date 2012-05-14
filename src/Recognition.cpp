/*
 * Recognition.cpp
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#include "Recognition.h"

Recognition::Recognition() {
	this->conversion = new SensorConversion();

	//Instanciation des capteurs avec le PIN
	this->captorBL = new Sensor(SENSOR_BOTTOM_LEFT, this->conversion);
	this->captorBM = new Sensor(SENSOR_BOTTOM_MIDDLE, this->conversion);
	this->captorBR = new Sensor(SENSOR_BOTTOM_RIGHT, this->conversion);

	this->captorTL = new Sensor(SENSOR_TOP_LEFT, this->conversion);
	this->captorTM = new Sensor(SENSOR_TOP_MIDDLE, this->conversion);
	this->captorTR = new Sensor(SENSOR_TOP_RIGHT, this->conversion);
}

bool Recognition::isBetween(int min, int max, int value) {
	if(value >= min && value <= max) {
		return true;
	}
	return false;

}

/*
 * EnvironEgal retourne true quans l'écart entre value1 et value2 est inférieur ou egale à ecartmax
 */
bool Recognition::around(int value1, int value2, int ecartmax) {
	if(value1 >= value2) {
		if((value1 - value2) <= ecartmax) {
			return true;
		}
	} else {
		if((value2 - value1) <= ecartmax) {
			return true;
		}
	}
	return false;
}

//Renvoie true de manière plus restrictive que isWall(), car il faut que les capteurs soit bien positionné
bool Recognition::isWallParallel() {
	//Le capteur du milieu sert de référence
	//Distance que les capteurs des cotés doivent avoir
	int side = (this->captorBM->get()) / (cos(ANGLE_BETWEEN_CAPTOR));

	//Distance qu'ils ont réellement
	int left = this->captorBL->get();
	int right = this->captorBR->get();

	//Comparaison des valeurs théoriques et réels avec une tolérance à l'erreur de ALLOW_ERROR mm
	if(isBetween(side - ALLOW_ERROR, side + ALLOW_ERROR, left)) {
		if(isBetween(side - ALLOW_ERROR, side + ALLOW_ERROR, right)) {
			return true;
		}
	}

	return false;
}

bool Recognition::isWall() {
	//Un mur n'est visible que par les capteurs du bas, mais il faut les 3

	if(this->isBetween(20, 50, this->captorBL->get())) {
		if(this->isBetween(20, 50, this->captorBM->get())) {
			if(this->isBetween(20, 50, this->captorBR->get())) {
				return true;
			}
		}
	}

	return false;
}

bool Recognition::isCD() {
	//Un CD n'est visible que par les capteurs du bas, ne bouge pas, et n'est que sur un seul capteur à la fois
	//Renvoie true entre 20 et 50cm

	if(!this->isObstacle()) {
		if(this->isBetween(20, 50, this->captorBL->get()) || this->isBetween(20, 50, this->captorBM->get()) || this->isBetween(20, 50, this->captorBR->get())) {
			return true;
		}
	}

	return false;
}
bool Recognition::isObstacle() {
	//Un obstacle est visible que par 2 capteurs alignée verticalement et ne bouge pas
	//Renvoie true entre 20 et 30cm

	if(this->isBetween(20, 50, this->captorBL->get()) && this->isBetween(20, 50, this->captorTL->get())) {
		return true;
	} else if(this->isBetween(20, 50, this->captorBM->get()) && this->isBetween(20, 50, this->captorTM->get())) {
		return true;
	} else if(this->isBetween(20, 50, this->captorBR->get()) && this->isBetween(20, 50, this->captorTR->get())) {
		return true;
	}

	return false;
}
bool Recognition::isRobot() {
	//Un robot peut être vu que par un (ou deux) capteurs en mêmes temps (bas ou/et haut) et est le seul à bouger
	//Renvoie true entre 20 et 30cm

	if(!this->isCD() && !this->isObstacle()) {
		if(this->isBetween(20, 50, this->captorBL->get()) || this->isBetween(20, 50, this->captorBM->get()) || this->isBetween(20, 50, this->captorBR->get())) {
			return true;
		}
	}

	return false;
}

int Recognition::getDistanceBL() {
return this->captorBL->get();
}

int Recognition::getDistanceBR() {
return this->captorBR->get();
}

int Recognition::getDistanceBM() {
return this->captorBM->get();
}

int Recognition::getDistanceTR() {
return this->captorTR->get();
}

int Recognition::getDistanceTL() {
return this->captorTL->get();
}

int Recognition::getDistanceTM() {
return this->captorTM->get();
}
