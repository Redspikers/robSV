#ifndef VOLET_H
#define VOLET_H

#include <Servo.h>

#define ANGLE_OUVERTURE
#define ANGLE_FERMETURE

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
