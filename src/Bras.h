#ifndef __BRAS__
#define __BRAS__

#include "include.h"

//Temps d'éxecution des moteurs pour le mouvement 1 (Chopper le CD)
#define TEMPS_EPAULE1    30
#define TEMPS_COUDE1     20
//Temps d'éxecution des moteurs pour le mouvement 2 (Amener au tapis)
#define TEMPS_EPAULE2    30
#define TEMPS_COUDE2     20
//Temps d'éxecution des moteurs pour le mouvement 3 (Retour position initiale)
#define TEMPS_EPAULE3    30
#define TEMPS_COUDE3     20

#define VITESSE_MOTEUR  40 //Vitesse de rotation du moteur

class Bras
{
    public:
    Bras(); 
    boolean attrapeCD();
    int getCapteurCouleur();


    private:
    Servomoteur* servoCoude;
    Servomoteur* servoEpaule;
    Pompe* pompe;
    
};

#endif