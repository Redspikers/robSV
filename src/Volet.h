#ifndef VOLET_H
#define VOLET_H

#include "include.h"

#define ANGLE_OUVERTURE_DROITE
#define ANGLE_OUVERTURE_GAUCHE
#define ANGLE_FERMETURE_GAUCHE
#define ANGLE__FERMETURE_DROITE

class Volet
{
    public:
        Volet();
        void closeVolet();
        void openVolet();


    private:
        Servo* servoVoletGauche; //Droite et gauche déf par rapport
								//à la marche avant du robot (choix arbitraire)
        Servo* servoVoletDroite;

};

#endif // VOLET_H
