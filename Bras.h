#ifndef __BRAS__
#define __BRAS__

#include "constantes.h"

class Bras
{
    public:
    Bras(); 
    bool attrapeCD();
    int getCapteurCouleur();


    private:
    Servomoteur servoCoude;
    Servomoteur servoEpaule;
    int capteurCouleur;//int pour le moment
    int pompe;
    
};

#endif