#include "Volet.h"

Volet::Volet()
{
    this->servoVolet = new Servo();

}

// TODO : le fonctionnement ici d�pend du sens de montage des servo moteur m�caniquement
// TODO : Servo a monter m�caniquement soit en position 0, 90 ou 180

Volet::openVolet()
{

    this->servoVolet -> write(ANGLE_OUVERTURE);

}


Volet::closeVolet()
{

    this-> servoVolet -> write(ANGLE_FERMETURE);
}


