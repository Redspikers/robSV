#include "Gate.h"

Gate::Gate() {
    this->servoGateRight = new Servo();
    this->servoGateLeft = new Servo();

}

// TODO : le fonctionnement ici dépend du sens de montage des servo moteur mécaniquement
// TODO : Servo a monter m�caniquement soit en position 0, 90 ou 180
//droite et gauche choisis arbitrairement dans le sens de la marche avant du robot
void Gate::openGate() {

    this->servoGateRight->write(Gate::ANGLE_OPEN_RIGHT);
    this->servoGateLeft->write(Gate::ANGLE_OPEN_LEFT);

}


void Gate::closeGate() {

    this->servoGateRight->write(Gate::ANGLE_CLOSE_RIGHT);
    this->servoGateLeft->write(Gate::ANGLE_CLOSE_LEFT);
}


