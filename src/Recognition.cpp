/*le but de ce bout de code est d'interpreter les données reçus par les capteurs
 * de distance infra rouge. Ceci afin de déterminer quel type d'obstacle à été
 * détecté (vu) et quelles valeurs relevés par le capteurs peuvent être considérées
 * comme analysable
 */

/*
 * Obstacle potentiels :
 * Quelconque
 * CD
 *
 * Positions des obstacles :
 * découpage de la zone couverte par les capteur du bas en 5 zones :
 * 1 - Gauche
 * 2 - Milieu Gauche
 * 3 - Milieu
 * 4 - Milieu Droite
 * 5 - Droite
 *
 * A gauche (pour les obstacle de nature indeterminés)
 * A Droite
 * Devant pres (Entre 20 et 50 cm devant)
 * Devant loin (plus de 60cm)
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
	this->captorBack = new Sensor(SENSOR_BACK, this->conversion);
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

//Renvoie true de manière plus restrictive que hasWallAhead(), car il faut que les capteurs soit
bool Recognition::hasWallParallel() {
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

bool Recognition::hasWall() {
	if(20 < this->captorBL->get() && this->captorBL->get() < 50) {
		if(20 < this->captorBM->get() && this->captorBM->get() < 50) {
			if(20 < this->captorBR->get() && this->captorBR->get() < 50) {
				return true;
			}
		}
	}

	return false;
}

int Recognition::getDistanceBL() {
	return this->captorBL->get();
}
