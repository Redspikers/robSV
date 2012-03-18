#include "Volet.h"

Volet::Volet()
{
    this->servoVolet = new Servo();

}

// TODO : le fonctionnement ici dépend du sens de montage des servo moteur mécaniquement
// TODO : Servo a monter mécaniquement soit en position 0, 90 ou 180

Volet::openVolet()
{

    this->servoVolet -> write(ANGLE_OUVERTURE);

}


Volet::closeVolet()
{

    this-> servoVolet -> write(ANGLE_FERMETURE);
}


