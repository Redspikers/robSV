/*
 * Node.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include "Cell.h"

class Node {
	public:
		Node(Cell *cell);
		~Node();

		void setCost(int cost);
		int getCost();

		void setParent(Node *parent);
		Node *getParent();

		void setNext(Node* next);
		Node* getNext();

		Cell* getCell();

	private:
		Cell* cell;
		int cost;

		Node* parent;
		Node* next;

};
#endif

