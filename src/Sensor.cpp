#include "Sensor.h"

Sensor::Sensor(int pinN, SensorConversion* conversion) {
	this->pinNumber = pinN;
	this->conversion = conversion;
}

//Renvoie la distance - quelle angle de portée ? ---> angle très très reduit : capteur infrarouge ultra directif
int Sensor::get() {
	int valeur = 0;
	int i = 0;
	int borne_inf[] = { 160, 0 };

	//Pour plus de precision, on prend 20 valeurs et on fait une moyenne
	for (i = 0; i < 20; i++) {
		valeur += analogRead(this->pinNumber);
	}
	valeur /= 20;

	//On approxime la distance en utilisant le tableau
	for (i = 0; i < 12; i++) {
		if ((valeur < this->conversion->get(i, 1))
				&& (valeur >= borne_inf[1])) {
			return (int) (borne_inf[0]
					+ ((valeur - borne_inf[1])
							/ (float) (borne_inf[1]
									- this->conversion->get(i, 1)) * 10));
		}
		borne_inf[0] = this->conversion->get(i, 0);
		borne_inf[1] = this->conversion->get(i, 1);
	}

	return 20;
}
