/*
 * Definition.h
 *
 *  Created on: 11 mai 2012
 *      Author: Koudja
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_


// Valeur minimum analogique renvoyé par le capteur de couleur pour choper du blanc
// TODO : A ETALONNER SUR PLACE

#define VAL_ANALOG_WHITE 600


//Variables de zones
#define MAX_INSIDE_CD 4
#define MAX_CAPTAIN_CD 4

//Some specifities
#define ROBOT_WIDTH 340
#define ROBOT_HEIGHT 290

#define MAP_WIDTH 3000
#define MAP_HEIGHT 2000

#define DELAY_BEFORE_STARTING 5000
#define DELAY_BEFORE_MOVING 2000
#define DELAY_BEFORE_STOP 85000

//Angle des capteurs et erreur (en MM) autorisées lors des comparaisons théoriques (trigonométire) et réels
#define ANGLE_BETWEEN_CAPTOR 30
#define ALLOW_ERROR 40 //TODO calibrer

//Allonge du bras entre la fin du robot et la ventouse au sol
#define ARM_REACH 90

//Angle de la porte
#define GATE_ANGLE_OPEN 0
#define GATE_ANGLE_CLOSE 95

//Where the robot start
#define START_LEFT_X 150
#define START_LEFT_Y 1750
#define START_LEFT_ANGLE 0

#define START_RIGHT_X 2850
#define START_RIGHT_Y 1750
#define START_RIGHT_ANGLE 180

//Zone - where to drop CDs
#define CAPTAIN_LEFT_X 250
#define CAPTAIN_LEFT_Y 1750

#define CAPTAIN_RIGHT_X 2750
#define CAPTAIN_RIGHT_Y 1750

#define STOCK_LEFT_X 200
#define STOCK_LEFT_Y 1000

#define STOCK_RIGHT_X 2800
#define STOCK_RIGHT_Y 1000



//CDs
#define CD_TL_X 1000
#define CD_TL_Y 1500

#define CD_TR_X 2000
#define CD_TR_Y 1500

#define CD_BL_X 450
#define CD_BL_Y 300

#define CD_BR_X 2550
#define CD_BR_Y 300

#define CD_MT_X 1500
#define CD_MT_Y 220

#define CD_MB_X 1500
#define CD_MB_Y 240

#define CD_ML_X 1425
#define CD_ML_Y 300

#define CD_MR_X 1575
#define CD_MR_Y 300

#define CD_PL_TL_X 890
#define CD_PL_TL_Y 1210

#define CD_PL_TM_X 1100
#define CD_PL_TM_Y 1240

#define CD_PL_TR_X 1310
#define CD_PL_TR_Y 1210

#define CD_PL_L_X 808
#define CD_PL_L_Y 1000

#define CD_PL_BL_X 890
#define CD_PL_BL_Y 790

#define CD_PL_BM_X 1100
#define CD_PL_BM_Y 760

#define CD_PL_BR_X 1210
#define CD_PL_BR_Y 790

#define CD_PR_TL_X 1690
#define CD_PR_TL_Y 1210

#define CD_PR_TM_X 1900
#define CD_PR_TM_Y 1240

#define CD_PR_TR_X 2110
#define CD_PR_TR_Y 1210

#define CD_PR_R_X 2140
#define CD_PR_R_Y 1000

#define CD_PR_BL_X 1690
#define CD_PR_BL_Y 790

#define CD_PR_BM_X 1900
#define CD_PR_BM_Y 760

#define CD_PR_BR_X 2110
#define CD_PR_BR_Y 790


// distance cd pour TAKE
#define DISTANCE_CD_TAKE 500



/*	epaule : angle 180 : déployé
 angle 90 : perpendiculaire au sol
 angle 0 : collision avec l'interieur du robot
 coude : angle 0 : déployé

 */
//Angle des moteurs pour le mouvement 1 (Chopper le CD)    //TODO
#define ANGLE_SHOULDER_TAKE 135
#define ANGLE_ELBOW_TAKE 90
//Angle des moteurs pour le mouvement 2 (Amener au tapis)      //TODO
#define ANGLE_SHOULDER_DROP 90
#define ANGLE_ELBOW_DROP 120
//Angle des moteurs pour le mouvement 3 (Retour position de recherche de CD)
#define ANGLE_SHOULDER_IDLE 140
#define ANGLE_ELBOW_IDLE 50
//Angle des servo pour la position idleBegin (position en début de match c'est tout)
#define ANGLE_SHOULDER_IDLE_BEGIN 90
#define ANGLE_ELBOW_IDLE_BEGIN 140

#endif /* DEFINITION_H_ */
