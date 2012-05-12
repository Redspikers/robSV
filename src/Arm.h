#ifndef __ARM__
#define __ARM__

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Pomp.h"
#include "SensorColor.h"

//Angle des moteurs pour le mouvement 1 (Chopper le CD)
#define ANGLE_SHOULDER_TAKE 30
#define ANGLE_ELBOW_TAKE 20
//Angle des moteurs pour le mouvement 2 (Amener au tapis)
#define ANGLE_SHOULDER_DROP 30
#define ANGLE_ELBOW_DROP 20
//Angle des moteurs pour le mouvement 3 (Retour position initiale)
#define ANGLE_SHOULDER_IDLE 30
#define ANGLE_ELBOW_IDLE 20

class Arm {
	public:
		Arm();
		void takeCD();
		void dropInside();
		void idle();

		bool hasCD();

	private:
		Servo* servoElbow;
		Servo* servoShoulder;
		Pomp* pomp;
		SensorColor* sensor;
};

#endif
