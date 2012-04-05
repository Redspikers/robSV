#include "Volet.h"



Volet::Volet()
{
    this->servoVoletDroite = new Servo();
    this->servoVoletGauche = new Servo();

}

// TODO : le fonctionnement ici dépend du sens de montage des servo moteur m�caniquement
// TODO : Servo a monter m�caniquement soit en position 0, 90 ou 180
//droite et gauche choisis arbitrairement dans le sens de la marche avant du robot
Volet::openVolet()
{

    this->servoVoletDroite -> write(ANGLE_OUVERTURE_DROITE);
    this->servoVoletGauche -> write(ANGLE_OUVERTURE_GAUCHE)

}


Volet::closeVolet()
{

    this-> servoVoletDroite -> write(ANGLE_FERMETURE_DROITE);
    this-> servoVoletGauche -> write(ANGLE_FERMETURE_GAUCHE);
}


