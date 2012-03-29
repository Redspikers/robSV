#ifndef __POMPE__
#define __POMPE__

#include "include.h"

class Pompe {
public:
	Pompe();
	void compresser();
	void relacher();

private:
	boolean compressee; //int pour l'instant

};

#endif
