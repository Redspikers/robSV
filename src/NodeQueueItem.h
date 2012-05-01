/*
 * NodeQueueItem.h
 *
 *  Created on: 30 avr. 2012
 *      Author: Koudja
 */

#ifndef NODEQUEUEITEM_H_
#define NODEQUEUEITEM_H_

#include <stdlib.h>
#include "Node.h"

class NodeQueueItem {
	public:
		NodeQueueItem(Node* node);
		virtual ~NodeQueueItem();

		Node* getNode();

		void setPrevious(NodeQueueItem* previous);
		NodeQueueItem* getPrevious();

		void setNext(NodeQueueItem* next);
		NodeQueueItem* getNext();


	private:
		Node* node;

		NodeQueueItem* previous;
		NodeQueueItem* next;
};

#endif /* NODEQUEUEITEM_H_ */
