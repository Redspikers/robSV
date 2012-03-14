#ifndef __BRAS__
#define __BRAS__

#include "constantes.h"

class Bras {
public:
	Bras();
	bool attrapeCD();
	int getCapteurCouleur();

private:
	Servo *servoCoude;
	Servo *servoEpaule;
	int capteurCouleur; //int pour le moment
	Pompe *pompe;

};

#endif
