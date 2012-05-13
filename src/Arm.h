#ifndef __ARM__
#define __ARM__

#include <Arduino.h>
#include <Servo.h>

#include "Pin.h"
#include "Pomp.h"
#include "SensorColor.h"


/*	epaule : angle 180 : déployé
			angle 90 : perpendiculaire au sol
			angle 0 : collision avec l'interieur du robot
	coude : angle 0 : déployé
			
*/
//Angle des moteurs pour le mouvement 1 (Chopper le CD) //TODO
#define ANGLE_SHOULDER_TAKE 135
#define ANGLE_ELBOW_TAKE 
//Angle des moteurs pour le mouvement 2 (Amener au tapis)
#define ANGLE_SHOULDER_DROP 90
#define ANGLE_ELBOW_DROP 120
//Angle des moteurs pour le mouvement 3 (Retour position de recherche de CD)
#define ANGLE_SHOULDER_IDLE 140
#define ANGLE_ELBOW_IDLE 50
//Angle des servo pour la position idleBegin (position en début de match c'est tout)
#define ANGLE_SHOULDER_IDLE_BEGIN 90
#define ANGLE_ELBOW_IDLE_BEGIN 140

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
