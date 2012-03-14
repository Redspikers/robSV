#include "Bras.h"

Bras::Bras() {

}

bool Bras::attrapeCD() {
	/*
	 * On verifie qu'il est de bonne couleur et on attrape le cd
	 * Si à n'importe quel moment , le CD est laché (et donc le capteur ne voit plus rien)
	 * On retourne False
	 * On retourne True uniquement dans le cas où tout s'est bien passé 
	 * (bonne couleur & pas laché en cours & laché au dessus du tapis et retour position initiale
	 * */

	//Mouvement des deux servos. Le même tout le temps ?

	//Compresion de la pompe 
	this->pompe->compresser();

	//Mouvement des servos pour aller au tapis

	//Relachement au dessus du tapis
	this->pompe->compresser();

	//Retour position initiale

	return true;
}

int Bras::getCapteurCouleur() {
	//return capteur.read(); ?
	return 0;
}

