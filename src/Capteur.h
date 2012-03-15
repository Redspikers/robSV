#ifndef __CAPTEUR__
#define __CAPTEUR__

#include "include.h"

class Capteur {
public:
	Capteur(int pinN);
	int get();

private:
	int pinNumber; //int pour l'instant

};

#endif
