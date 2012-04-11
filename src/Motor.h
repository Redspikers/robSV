#ifndef MOTOR_H_
#define MOTOR_H_

#include "include.h"

class Motor {
private:
	Servo *servoLeft;
	Servo *servoRight;

	boolean attached;

public:
	Motor();
	virtual ~Motor();

	void attach(int pinLeft, int pinRight);
	void detach();
	boolean isAttached();

	void move(int distanceMM);
	void turn(int angleDegree, int distanceMM);
};

#endif /* MOTOR_H_ */