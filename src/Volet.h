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
        Servomoteur* servoVolet;

};

#endif // VOLET_H
