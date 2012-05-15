#include "SensorConversionBlue.h"
#include <new.h>
SensorConversionBlue::SensorConversionBlue() {
	this->conversion = new int*[9];

	this->conversion[0] = new int[2];
	this->conversion[0][0] = 80;
	this->conversion[0][1] = 98;

	this->conversion[1] = new int[2];
	this->conversion[1][0] = 70;
	this->conversion[1][1] = 100;

	this->conversion[2] = new int[2];
	this->conversion[2][0] = 60;
	this->conversion[2][1] = 115;

	this->conversion[3] = new int[2];
	this->conversion[3][0] = 50;
	this->conversion[3][1] = 130;

	this->conversion[4] = new int[2];
	this->conversion[4][0] = 40;
	this->conversion[4][1] = 155;

	this->conversion[5] = new int[2];
	this->conversion[5][0] = 30;
	this->conversion[5][1] = 200;

	this->conversion[6] = new int[2];
	this->conversion[6][0] = 20;
	this->conversion[6][1] = 290;

	this->conversion[7] = new int[2];
	this->conversion[7][0] = 15;
	this->conversion[7][1] = 360;

	this->conversion[8] = new int[2];
	this->conversion[8][0] = 10;
	this->conversion[8][1] = 530;

}

SensorConversionBlue::~SensorConversionBlue() {

}

int SensorConversionBlue::get(int i, int j) {
	return this->conversion[i][j];
}

