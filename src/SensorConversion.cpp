/*
 * SensorConversion.cpp
 *
 *  Created on: 6 mai 2012
 *      Author: Koudja
 */

#include "SensorConversion.h"
#include <new.h>
SensorConversion::SensorConversion() {
	this->conversion = new int*[12];

	this->conversion[0] = new int[2];
	this->conversion[0][0] = 80;
	this->conversion[0][1] = 144;

	this->conversion[1] = new int[2];
	this->conversion[1][0] = 70;
	this->conversion[1][1] = 170;

	this->conversion[2] = new int[2];
	this->conversion[2][0] = 60;
	this->conversion[2][1] = 195;

	this->conversion[3] = new int[2];
	this->conversion[3][0] = 50;
	this->conversion[3][1] = 235;

	this->conversion[4] = new int[2];
	this->conversion[4][0] = 40;
	this->conversion[4][1] = 296;

	this->conversion[5] = new int[2];
	this->conversion[5][0] = 30;
	this->conversion[5][1] = 384;

	this->conversion[6] = new int[2];
	this->conversion[6][0] = 20;
	this->conversion[6][1] = 492;

}

SensorConversion::~SensorConversion() {

}

int SensorConversion::get(int i, int j) {
	return this->conversion[i][j];
}

int SensorConversion::getSize() {
	return 7;
}
