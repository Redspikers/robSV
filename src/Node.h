/*
 * Node.h
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

class Node {
	public:
		Node(int x, int y, bool m_blocked);
		~Node();

		void setX(int x);
		int getX();

		void setY(int y);
		int getY();

		void setCost(int cost);
		int getCost();

		void setBlocked(bool blocked);
		bool isBlocked();

		void setParent(Node *parent);
		Node *getParent();

	private:
		int m_x; // position x
		int m_y; // position y
		bool m_blocked;
		int m_cost;
		Node *m_parent;
};
#endif

