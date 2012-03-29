#ifndef __BRAS__
#define __BRAS__

#include "include.h"

//Angle des moteurs pour le mouvement 1 (Chopper le CD)
#define ANGLE_EPAULE1    30
#define ANGLE_COUDE1     20
//Angle des moteurs pour le mouvement 2 (Amener au tapis) 
#define ANGLE_EPAULE2    30
#define ANGLE_COUDE2     20
//Angle des moteurs pour le mouvement 3 (Retour position initiale)
#define ANGLE_EPAULE3    30
#define ANGLE_COUDE3     20


class Bras
{
    public:
    Bras(); 
    boolean attrapeCD();
    int getCapteurCouleur();


    private:
    Servo* servoCoude;
    Servo* servoEpaule;
    Pompe* pompe;
    
};

#endif