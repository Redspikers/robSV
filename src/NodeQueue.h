/*
 * NodeQueue.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef NODEQUEUE_H_
#define NODEQUEUE_H_

#include <stdlib.h>
#include "Cell.h"
#include "Node.h"
#include "NodeQueueItem.h"

class NodeQueue {
	public:
		NodeQueue();
		~NodeQueue(void);

		void push(Node* item);
		int size();
		//bool containsCell(Cell* item);
		NodeQueueItem* getItem(Node* node);
		Node* getNode(int i);
		Node* getNode(Cell* cell);
		void remove(Node* item);

		NodeQueueItem* getFirst();

	protected:
		NodeQueueItem* first;

		int count;
};

#endif /* NODEQUEUE_H_ */
