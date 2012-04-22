/*
 * NodeQueue.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef NODEQUEUE_H_
#define NODEQUEUE_H_

#include <stdlib.h>
#include "Node.h"

class NodeQueue {
	public:
		NodeQueue();
		NodeQueue(const NodeQueue &otherNodeQueue);
		~NodeQueue(void);

		void push(Node *item);
		Node* pop(void);
		int size();
		bool contains(Node *item);
		Node* get(int i);
		void remove(Node *item);

	protected:
		Node **data;
		int beginning;
		int end;

		int count;
};

#endif /* NODEQUEUE_H_ */
