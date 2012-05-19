#include "SensorConversionBlue.h"
#include <new.h>
SensorConversionBlue::SensorConversionBlue() {
	this->conversion = new int*[5];


	this->conversion[0] = new int[2];
	this->conversion[0][0] = 30;
	this->conversion[0][1] = 180;

	this->conversion[1] = new int[2];
	this->conversion[1][0] = 25;
	this->conversion[1][1] = 190;

	this->conversion[2] = new int[2];
	this->conversion[2][0] = 20;
	this->conversion[2][1] = 210;

	this->conversion[3] = new int[2];
	this->conversion[3][0] = 15;
	this->conversion[3][1] = 255;

	this->conversion[4] = new int[2];
	this->conversion[4][0] = 10;
	this->conversion[4][1] = 320;

}

SensorConversionBlue::~SensorConversionBlue() {

}

int SensorConversionBlue::get(int i, int j) {
	return this->conversion[i][j];
}

int SensorConversionBlue::getSize() {
	return 5;
}
