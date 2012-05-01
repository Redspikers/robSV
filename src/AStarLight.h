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

#include "Node.h"
#include "NodeQueue.h"
#include "NodeQueueItem.h"
#include "Map.h"
//#include "Robot.h"

class AStarLight {
	public:
		AStarLight(Map* map, int radius);
		~AStarLight();

		Node* compute(Cell* begin, Cell* end);

	private:
		int radius;
		Map* map;
		NodeQueue* openList;
		Node* closedList;


};

#endif /* ASTARLIGHT_H_ */
