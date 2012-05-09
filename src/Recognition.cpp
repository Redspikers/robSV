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

	//Les différents capteurs
	this->captorBL = new Sensor(Pin::SENSOR_BOTTOM_LEFT, this->conversion);
	this->captorBM = new Sensor(Pin::SENSOR_BOTTOM_MIDDLE, this->conversion);
	this->captorBR = new Sensor(Pin::SENSOR_BOTTOM_RIGHT, this->conversion);

	this->captorTL = new Sensor(Pin::SENSOR_TOP_LEFT, this->conversion);
	this->captorTM = new Sensor(Pin::SENSOR_TOP_MIDDLE, this->conversion);
	this->captorTR = new Sensor(Pin::SENSOR_TOP_RIGHT, this->conversion);
	this->captorBack = new Sensor(Pin::SENSOR_BACK, this->conversion);

	this->valeur = new int[7];
	this->distancesObstacles = new int[9];
}

void Recognition::analyse() {
	/*
	 * ****** TRAITEMENT OBSTACLES ****** (Voir tableau excel "obstacles.xls")
	 * 0 Si seulement bas gauche compris entre 20 et 50cm : CD gauche
	 * 1 Si bas Milieu uniquement compris entre 20 et 50cm  : CD au milieu
	 * 2 Si seulement bas droite compris entre 20 et 50cm  : CD Droite
	 * 3 SI haut droit et bas droit compris entre 20 et 150 cm et ~ egales : Obstacle à Droite a Xcm
	 * 4 SI haut gauche et bas gauche compris entre 20 et 150cm et ~ egales : Obstacle à gauche a Xcm
	 * 5 Si  milieu  entre 20 et 49cm : Obstacle devant à Xcm
	 * 6 Si arrière entre 20 et 150 cm: Obstacle derrière
	 */

	//*******OBSTACLE CD*************

	if (comprisEntre(20, 50, this->valeur[5])) {
		this->distancesObstacles[0] = this->valeur[5]; //CD GAUCHE
	}else{
			this->distancesObstacles[0] = 0; //On supprime CD Gauche
		}

	//Bas Droit
	if (comprisEntre(20, 50, this->valeur[3])) {
		this->distancesObstacles[2] = this->valeur[3]; //CD Droit
	}else {
			this->distancesObstacles[2] = 0; //On supprime CD Droit
		}


	//CD MILIEU
	if ( comprisEntre(20, 50, this->valeur[4])) {
		this->distancesObstacles[1] = this->valeur[4];
	} else {
		this->distancesObstacles[1] = 0;
	}

	//**********AUTRES OBSTACLES*****************


	//Haut droit et bas droit
	if (comprisEntre(20, 150, this->valeur[0]) && comprisEntre(20, 150, this->valeur[3]) && environEgal(this->valeur[3], this->valeur[0], 20)) {
		this->distancesObstacles[3] = this->valeur[0]; //Obstacle à Droite à Xcm
	} else {
		this->distancesObstacles[3] = 0;
	}

	//Haut Gauche et bas Gauche
	if (comprisEntre(20, 150, this->valeur[1]) && comprisEntre(20, 150, this->valeur[5]) && environEgal(this->valeur[1], this->valeur[5], 20)) {
		this->distancesObstacles[4] = this->valeur[1]; //Obstacle à Gauche à Xcm
	} else {
		this->distancesObstacles[4] = 0;
	}



	//Milieu
	if (comprisEntre(20, 150, this->valeur[2])) {
		this->distancesObstacles[5] = this->valeur[2]; //Obstacle au milieu à Xcm
	} else {
		this->distancesObstacles[5] = 0;
	}
	// Arrière
	if (comprisEntre(20, 150, this->valeur[6])) {
		this->distancesObstacles[6] = this->valeur[6]; //Obstacle à Gauche à Xcm
	} else {
		this->distancesObstacles[6] = 0;
	}
}

void Recognition::getValues() {
	this->valeur[0] = this->captorTR->get();
	this->valeur[1] = this->captorTL->get();
	this->valeur[2] = this->captorTM->get();
	this->valeur[3] = this->captorBR->get();
	this->valeur[4] = this->captorBM->get();
	this->valeur[5] = this->captorBL->get();
	this->valeur[6] = this->captorBack->get();
}

bool Recognition::comprisEntre(int min, int max, int value) {
	if (value >= min && value <= max) {
		return true;
	}
	return false;

}

/*
 * EnvironEgal retourne true quans l'écart entre value1 et value2 est inférieur ou egale à ecartmax
 */
bool Recognition::environEgal(int value1, int value2, int ecartmax) {
	if (value1 >= value2) {
		if ((value1 - value2) <= ecartmax) {
			return true;
		}
	} else {
		if ((value2 - value1) <= ecartmax) {
			return true;
		}
	}
	return false;
}

/*
 *Retourne un tableau d'entiers corespondant au valeurs des distances par rapport aux different obstacle.
 * Si la valeur = 0 pas d'obstacle
 *
 *Correspondance des indice du tableau "distanceObstacles"
 * 0  CD gauche
 * 1  CD au milieu
 * 2  CD Droite
 * 3  Obstacle à Droite
 * 4  Obstacle à gauche
 * 5  Obstacle devant (milieu)
 * 6  Obstacle derrière
 */


int* Recognition::getObstacles() {
	//Récupération des valeurs
	this->getValues();

	//Analyse pour créer le tableau d'obstacle
	this->analyse();

	//retour du tableau d'obstacles
	return this->distancesObstacles;
}
