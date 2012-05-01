/*
 * NodeQueue.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "NodeQueue.h"

NodeQueue::NodeQueue() {
	this->first = NULL;

	this->count = 0;
}

NodeQueue::~NodeQueue(void) {
	//TODO
}

void NodeQueue::push(Node* node) {
	NodeQueueItem* item = new NodeQueueItem(node);

	item->setPrevious(NULL);
	item->setNext(this->first);

	if(this->first != NULL) {
		this->first->setPrevious(item);
	}


	this->first = item;

	this->count = this->count + 1;
}

int NodeQueue::size() {
	return this->count;
}

/*
bool NodeQueue::containsCell(Cell* cell) {
	if(this->getNode(cell) != NULL) {
		return true;
	}
	return false;
}
*/

NodeQueueItem* NodeQueue::getItem(Node* node) {
	NodeQueueItem* current = this->first;

	while(current != NULL) {
		if(current->getNode() == node) {
			return current;
		}
		current = current->getNext();
	}

	return NULL;
}

Node* NodeQueue::getNode(Cell* cell) {
	NodeQueueItem* current = this->first;
	//std::cout << "         getNode cell : " << cell->getX() << cell->getY() << std::endl;

	while(current != NULL) {
		//std::cout << "         getNode node : " << current->getNode()->getCell()->getX() << current->getNode()->getCell()->getY() << std::endl;

		if(current->getNode()->getCell() == cell) {
			return current->getNode();
		}
		current = current->getNext();

	}
	//std::cout << "         getNode node : NULL"<< std::endl;

	return NULL;
}

Node* NodeQueue::getNode(int i) {
	NodeQueueItem* current = this->first;

	if(i < this->count) {
		for(int j=0 ; j < i ; j++) {
			current = current->getNext();
		}

		return current->getNode();
	}

	return NULL;
}

void NodeQueue::remove(Node* node) {
	NodeQueueItem* item = this->getItem(node);

	//std::cout << "      Remove node : " << node->getCell()->getX() << node->getCell()->getY() << std::endl;

	//std::cout << "      Remove item : " << item->getNode()->getCell()->getX() << item->getNode()->getCell()->getY() << std::endl;

	if(item != NULL) {
		NodeQueueItem* previous = item->getPrevious();
		NodeQueueItem* next = item->getNext();

		if(previous != NULL) {
			previous->setNext(next);
		}
		if(next != NULL) {
			next->setPrevious(previous);
		}

		this->count = this->count - 1;

		//Provoque le delete des previous et next ...
		//item->setPrevious(NULL);
		//item->setNext(NULL);
		//delete item;
	}
}

NodeQueueItem* NodeQueue::getFirst() {
	return this->first;
}
