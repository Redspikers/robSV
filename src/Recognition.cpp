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
    //Instanciation des capteurs avec le PIN

	//Les différents capteurs
	this->captorBL = new Sensor(Pin::CAPTOR_BOTTOM_LEFT);
	this->captorBM = new Sensor(Pin::CAPTOR_BOTTOM_MIDDLE);
	this->captorBR = new Sensor(Pin::CAPTOR_BOTTOM_RIGHT);

	this->captorTL = new Sensor(Pin::CAPTOR_TOP_LEFT);
	this->captorTM = new Sensor(Pin::CAPTOR_TOP_MIDDLE);
	this->captorTR = new Sensor(Pin::CAPTOR_TOP_RIGHT);

	this->valeur = new int[6];
	this->distancesObstacles = new int[9];
}

void Recognition::analyse(int* distancesObstacle[]) {
    /*
     * ****** TRAITEMENT OBSTACLES ****** (Voir tableau excel "obstacles.xls")
     * 0 Si seulement bas gauche compris entre 20 et 50cm : CD gauche
     * 1 SI bas Milieu et bas gauche compris entre 20 et 50cm  : CD au milieu Gauche
     * 2 Si bas Milieu uniquement compris entre 20 et 50cm  : CD au milieu
     * 3 Si seulement bas droite compris entre 20 et 50cm  : CD Droite
     * 4 SI bas Milieu et bas droite compris entre 20 et 50cm  : CD au milieu droite
     *
     * 5 SI haut droit et bas droit compris entre 20 et 150 cm et ~ egales : Obstacle à Droite a Xcm
     * 6 SI haut gauche et bas gauche compris entre 20 et 150cm et ~ egales : Obstacle à gauche a Xcm
     * 7 Si haut gauche et haut droit et milieu  entre 20 et 49cm : Obstacle devant à Xcm
     * 8 Si milieu > à 60cm : Obstacle loin devant
     */

    //*******OBSTACLE CD*************

    if (comprisEntre(20, 50, valeur[5])) {
        distancesObstacle[0] = valeur[5]; //CD GAUCHE
        if(comprisEntre(20,50,valeur[4])) {
        	distancesObstacle[1]= valeur[4]; //CD MILIEU GAUCHE
            distancesObstacle[0] = 0; //On supprime CD Gauche car en faite c'est "milieu" gauche
        }
    }

    //Bas Droit
    if( comprisEntre(20,50,valeur[3])) {
        distancesObstacle[3]= valeur[3]; //CD Droit
        if( comprisEntre(20,50,valeur[4])) {
            distancesObstacle[4]= valeur[4]; //CD MILIEU Droit
            distancesObstacle[3]=0; //On supprime CD Droit car en faite c'est "milieu" droit
        }
    }

    //CD MILIEU
    if(distancesObstacle[3]==0 && distancesObstacle[0]==0 && comprisEntre(20,50,valeur[4])) {
        distancesObstacle[2]=valeur[4];
    } else {
    	distancesObstacle[2]=0;
    }

    //**********AUTRES OBSTACLES*****************
    //Haut droit et bas droit
    if(comprisEntre(20,150,valeur[0]) && comprisEntre(20,150,valeur[3]) && environEgal(valeur[3],valeur[0],20)) {
    	distancesObstacle[5]=valeur[0]; //Obstacle à Droite à Xcm
    } else {
    	distancesObstacle[5]=0;
    }

    //Haut Gauche et bas Gauche
    if(comprisEntre(20,150,valeur[1]) && comprisEntre(20,150,valeur[5]) && environEgal(valeur[1],valeur[5],20)) {

        distancesObstacle[6]=valeur[1]; //Obstacle à Gauche à Xcm
    }else{
     distancesObstacle[6]=0;
    }

    //Haut Gauche et Haut droit et Milieu
    if(comprisEntre(20,50,valeur[1]) && comprisEntre(20,50,valeur[0]) && comprisEntre(20,55,valeur[2])) {
    	distancesObstacle[7]=valeur[2]; //Obstacle à Gauche à Xcm
    } else {
    	distancesObstacle[7]=0;
    }

    if(comprisEntre(60,150,valeur[2]))   //Milieu
    {
        distancesObstacle[8]=valeur[2]; //Obstacle à Gauche à Xcm

    }else{
         distancesObstacle[8]=0;
    }

}

void Recognition::getValues() {
    this->valeur[0] = this->captorTR->get();
    this->valeur[1] = this->captorTL->get();
    this->valeur[2] = this->captorTM->get();
    this->valeur[3] = this->captorBR->get();
    this->valeur[4] = this->captorBM->get();
    this->valeur[5] = this->captorBL->get();
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
    if (value1 >= value2){
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
 * 1 CD au milieu Gauche
 * 2  CD au milieu
 * 3  CD Droite
 * 4  CD au milieu droite
 * 5  Obstacle à Droite
 * 6  Obstacle à gauche
 * 7  Obstacle devant
 * 8  Obstacle loin devant
 */

int* Recognition::getObstacles() {
    //Récupération des valeurs
    this->getValues();

    //Analyse pour créer le tableau d'obstacle
    this->analyse(&distancesObstacles);

    //retour du tableau d'obstacles
    return	&this->distancesObstacles;
}