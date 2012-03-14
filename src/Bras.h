#ifndef __BRAS__
#define __BRAS__

#include "include.h"

class Bras
{
    public:
    Bras(); 
    boolean attrapeCD();
    int getCapteurCouleur();


    private:
    Servomoteur* servoCoude;
    Servomoteur* servoEpaule;
    int capteurCouleur;//int pour le moment
    Pompe* pompe;
    
};

#endif