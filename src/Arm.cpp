#include "Arm.h"

Arm::Arm() {
	
	this->servoElbow = new Servo();
	this->servoShoulder = new Servo();
	this->pomp = new Pomp();
	this->sensor = new SensorColor();

	this->servoElbow->attach(ELBOW);
	this->servoShoulder->attach(SHOULDER);

}

//A n'utiliser que avant le début du match. Inutile pendant le match
void Arm::idleBegin() {
	
	
	this->servoElbow->write(ANGLE_ELBOW_IDLE_BEGIN); //Elbow
	this->servoShoulder->write(ANGLE_SHOULDER_IDLE_BEGIN); //Shoulder
	
}


void Arm::exitIdleBegin()
{
	this->move(ANGLE_SHOULDER_IDLE_BEGIN, ANGLE_SHOULDER_IDLE, 0);
	this->move(ANGLE_ELBOW_IDLE_BEGIN, ANGLE_ELBOW_IDLE, 1);
	 //le bras se trouve alors en position "Idle"
}


void Arm::takeCD() {
	
	this->move(ANGLE_ELBOW_IDLE, ANGLE_ELBOW_TAKE, 1);
	this->move(ANGLE_SHOULDER_IDLE, ANGLE_SHOULDER_TAKE, 0);
	
	this->dropInside();	
	//Dans tout les cas, on revient à la position initiale
	this->idle();
}

void Arm::dropInside() {
	//Mouvement des servos pour aller au tapis
	this->move(ANGLE_ELBOW_TAKE, ANGLE_ELBOW_DROP, 1);
	this->move(ANGLE_SHOULDER_TAKE, ANGLE_SHOULDER_DROP, 0);
	
	
	//Relachement au dessus du tapis
	this->pomp->drop();

}

bool Arm::hasCD() {
	if(digitalRead(PUSH_CD) == 1) {
		return true;
	}

	return false;
}


void Arm::idle()
{
	
	//Retour position initiale
	this->move(ANGLE_SHOULDER_DROP, ANGLE_SHOULDER_IDLE, 0);
	this->move(ANGLE_ELBOW_DROP, ANGLE_ELBOW_IDLE, 1);
	
	//FIN Mouvement
}


/* move : Passe le servo de angleBegin à angleEnd
		
			choix du servo : bool servo
			 if (servo == 0)  -----> Epaule
			 if (servo == 1) ------> Coude
			
			*/
void Arm::move(int angleBegin, int angleEnd, bool servo)
{
	int i;
	if(angleBegin<angleEnd)
	{
		if(servo == 0)
		{
			for(i=angleBegin; i<angleEnd; i++)
			{
				this->servoShoulder->write(i); 
				delay(5);
			}
		}
		else
		{
			for(i=angleBegin; i<angleEnd; i++)
			{
				this->servoElbow->write(i);
				delay(5); 
			}
		}
	}
	
	else if(angleBegin > angleEnd)
	{
		if(servo == 0)
		{
			for(i=angleBegin; i >=angleEnd; i--)
			{
				
				this->servoShoulder->write(i); 
				delay(5);
			}
		}
		else
		{
			for(i=angleBegin; i>=angleEnd; i--)
			{
				this->servoElbow->write(i); 
				delay(5);
			}
		}

	}
}
