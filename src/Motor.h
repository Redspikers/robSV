#ifndef MOTOR_H_
#define MOTOR_H_

#include "include.h"
#include <math.h>  // Peux etre virer si besoin d'optimisation niveau mémoire : besoin uniquement de cosinus.

class Motor {
private:
	Servo *servoLeft;
	Servo *servoRight;
	int pos;
	boolean attached;
	int distanceRight;
	int distanceLeft;

public:
	Motor();
	virtual ~Motor();

	void attach(int pinLeft, int pinRight);
	void detach();
	boolean isAttached();
	void back(int distanceMM);
	void move(int distanceMM);
	void turn(int angleDegree, int distanceMM);
};

#endif /* MOTOR_H_ */
