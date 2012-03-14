#ifndef MOTOR_H_
#define MOTOR_H_

#include <Servo.h>

class Motor {
private:
	Servo *servoLeft;
	Servo *servoRight;

	bool attached;

public:
	Motor();
	virtual ~Motor();

	void attach(int pinLeft, int pinRight);
	void detach();
	bool isAttached();

	void move(int distanceMM);
	void turn(int angleDegree, int distanceMM);
};

#endif /* MOTOR_H_ */
