#ifndef __PORTE__
#define __PORTE__

#include "include.h"

class Porte {
public:
	Porte();
	void ouvrir();
	void fermer();

private:
	boolean ouvert;
	Servo* servoVolet1;
    Servo* servoVolet2;

};

#endif
