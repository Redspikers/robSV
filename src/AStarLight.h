/*
 * AStarLight.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef ASTARLIGHT_H_
#define ASTARLIGHT_H_

#include <stdlib.h>
#include <math.h>
#include <newarray.h>

#include "Node.h"
#include "NodeQueue.h"
#include "Map.h"

class AStarLight {
	public:
		AStarLight();
		AStarLight(Map* map);
		virtual ~AStarLight();

		bool compute(Node* begin, Node* end);
		Node* getBestNode();

	private:
		Map *map;
		NodeQueue *openList;
		NodeQueue *closedList;


};

#endif /* ASTARLIGHT_H_ */
