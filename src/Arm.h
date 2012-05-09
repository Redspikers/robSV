#ifndef __ARM__
#define __ARM__

#include <Arduino.h>
#include <Servo.h>
#include "Pomp.h"
#include "SensorColor.h"

class Arm {
	public:
		//Angle des moteurs pour le mouvement 1 (Chopper le CD)
		static const int ANGLE_SHOULDER_TAKE = 30;
		static const int ANGLE_ELBOW_TAKE = 20;
		//Angle des moteurs pour le mouvement 2 (Amener au tapis)
		static const int ANGLE_SHOULDER_DROP = 30;
		static const int ANGLE_ELBOW_DROP = 20;
		//Angle des moteurs pour le mouvement 3 (Retour position initiale)
		static const int ANGLE_SHOULDER_IDLE = 30;
		static const int ANGLE_ELBOW_IDLE = 20;

		Arm(int pinElbow, int pinShoulder, int pinPomp, int pinPushButton, int pinSensorColor);
		void takeCD();
		void dropInside();
		void idle();

		bool hasCD();


	private:
		int angleShoulderTake;
		int angleElbowTake;

		int angleShoulderDrop;
		int angleElbowDrop;

		int angleShoulderIdle;
		int angleElbowIdle;

		Servo* servoElbow;
		Servo* servoShoulder;
		Pomp* pomp;
		SensorColor* sensor;

		int pinElbow;
		int pinShoulder;
		int pinPushButton;

};

#endif
