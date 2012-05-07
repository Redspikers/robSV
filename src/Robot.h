/*
 * Robot.h
 *
 *  Created on: 28 avr. 2012
 *      Author: Koudja
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>
#include "Map.h"
#include "AStarLight.h"
#include "Arm.h"
#include "Conveyor.h"
#include "Motor.h"
#include "Recognition.h"

class Robot {
	public:
		enum State {
			IDLE,
			SEARCH,
			BACK,
			TAKE,
			DROP
		};

		enum Position {
			LEFT,
			RIGHT
		};

		/**
		 * Variables de configuration
		 */
		//Position de départ du robot - Qualifie les zones et la cellule de départ pour le robot
		static const Robot::Position START_POSITION = Robot::LEFT;
		//Place qu'occupe le robot pour le pathfinding
		static const int PLACE_RADIUS = 2;
		//Nombre de CD maximum que le robot peut contenir avant de retourner à la base
		static const int MAX_CD = 4;
		/*
		 *
		 */

		Robot();
		~Robot();

		//Fonctions de la arduino, reportées dans cette classe
		void setup();
		void loop();

		//Fonctions spécifiques à chaque états
		void actionIdle();
		void actionSearch();
		void actionBack();
		void actionTake();
		void actionDrop();


	private:
		//Etat du robot temps en temps réel (détermine le comportement)
		State state;

		//Carte
		Map* map;
		//Position actuelle du robot
		Cell* position;
		//Angle du robot - de 0 à 360 (0 correspond au robot aligné sur l'axe X (de la carte, i.e. les 3mètres) qui "regarde à droite")
		int angle;
		//Cible éventuel du robot
		Cell* target;

		//Nombre de CD qu'il contient
		int cds;

		//Recherche de chemin (pathfinding)
		AStarLight* pathfinding;
		//Résultat du pathfinding
		Node* path;

		//Bras
		Arm* arm;

		//Tapis
		Conveyor* conveyor;

		//Déplacement
		Motor* motor;

		//Reconnaissance (capteurs)
		Recognition* sensor;

		//Met à jour la Map via les capteurs
		bool updateMap();
		//Change l'état courant du robot
		void changeState(Robot::State newState);
		//Détermine si le robot a déjà un chemin à suivre ou non
		bool hasPath();
		//Bouge le robot, met à jour la position, transcrit les cellules en distance réelles
		void move(Cell* destination);
		//Tourne le robot
		void turn(int newAngle);
		//Recherche le CD le plus proche, et s'arrête à la bonne cellule pour le bras puisse le prendre
		void findPathToCD();

		void findPathToBack();

		int diffAngle(Cell* destination);
};

#endif /* ROBOT_H_ */
