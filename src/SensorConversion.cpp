/*
 * SensorConversion.cpp
 *
 *  Created on: 6 mai 2012
 *      Author: Koudja
 */

#include "SensorConversion.h"

SensorConversion::SensorConversion() {
	this->conversion = new int*[12];

	this->conversion[0] = new int[2];
	this->conversion[0][0] = 130;
	this->conversion[0][1] = 87;

	this->conversion[1] = new int[2];
	this->conversion[1][0] = 120;
	this->conversion[1][1] = 95;

	this->conversion[2] = new int[2];
	this->conversion[2][0] = 110;
	this->conversion[2][1] = 105;

	this->conversion[3] = new int[2];
	this->conversion[3][0] = 100;
	this->conversion[3][1] = 115;

	this->conversion[4] = new int[2];
	this->conversion[4][0] = 90;
	this->conversion[4][1] = 131;

	this->conversion[5] = new int[2];
	this->conversion[5][0] = 80;
	this->conversion[5][1] = 144;

	this->conversion[6] = new int[2];
	this->conversion[6][0] = 70;
	this->conversion[6][1] = 170;

	this->conversion[7] = new int[2];
	this->conversion[7][0] = 60;
	this->conversion[7][1] = 195;

	this->conversion[8] = new int[2];
	this->conversion[8][0] = 50;
	this->conversion[8][1] = 235;

	this->conversion[9] = new int[2];
	this->conversion[9][0] = 40;
	this->conversion[9][1] = 296;

	this->conversion[10] = new int[2];
	this->conversion[10][0] = 30;
	this->conversion[10][1] = 384;

	this->conversion[11] = new int[2];
	this->conversion[11][0] = 20;
	this->conversion[11][1] = 492;

}

SensorConversion::~SensorConversion() {

}

int SensorConversion::get(int i, int j) {
	return this->conversion[i][j];
}

