#include "SensorBlue.h"

SensorBlue::SensorBlue(int pinN, SensorConversionBlue* conversion) {
	this->pinNumber = pinN;
	this->conversion = conversion;
}

//Renvoie la distance - quelle angle de portée ? ---> angle très très reduit : capteur infrarouge ultra directif
//Distance comprise entre 30 et 10 (si distance>30 ou distance<10 --> la valeur ne veut rien dire)
int SensorBlue::get() {
	int valeur = 0;
	int i = 0;
	int borne_inf[] = { 85, 0 };

	//Pour plus de precision, on prend 20 valeurs et on fait une moyenne
	for(i = 0; i < 20; i++) {
		valeur += analogRead(this->pinNumber);
	}
	valeur /= 20;

	//Si les valeurs sortent des bornes (à 5 près), on renvoit 0
	if((valeur < this->conversion->get(0, 1) - 5) || (valeur > this->conversion->get(4, 1) + 5))
		return 0;

	//On approxime la distance en utilisant le tableau
	for(i = 0; i < 5; i++) {
		if((valeur < this->conversion->get(i, 1)) && (valeur >= borne_inf[1])) {
			return (int) (borne_inf[0] + ((valeur - borne_inf[1]) / (float) (borne_inf[1] - this->conversion->get(i, 1)) * 5));
		}
		borne_inf[0] = this->conversion->get(i, 0);
		borne_inf[1] = this->conversion->get(i, 1);
	}

	return 10;
}
