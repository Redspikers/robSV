#include "Capteur.h"


Capteur::Capteur(int pinN){
	this->pinNumber = pinN;
}
Capteur::get(){
	return analogRead(this->pinNumber);
}