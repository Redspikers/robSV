#ifndef __CAPTOR__
#define __CAPTOR__

#include <Arduino.h>

class Captor {
public:
	//Tableau de conversion entre la valeur du capteur et la distance reelle
	static const int CONVERSION[12][2];

	Captor(int pinN);
	int get();

private:
	int pinNumber; //int pour l'instant

};

const int Captor::CONVERSION[12][2] = {
		{130, 87},
		{120, 95},
		{110,105},
		{100,115},
		{90, 131},
		{80, 144},
		{70, 170},
		{60, 195},
		{50, 235},
		{40, 296},
		{30, 384},
		{20, 492}
	};

#endif
