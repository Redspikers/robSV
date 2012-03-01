#ifndef __BRAS__
#define __BRAS__

#include "constantes.h"

class Bras
{
    public:
    bool atrapeCD();


    private:
    Servomoteur servoCoude;
    Servomoteur servoEpaule;
    int capteurCouleur;//int pour le moment
    int pompe;
    
};

#endif