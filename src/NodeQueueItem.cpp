/*
 * NodeQueueItem.cpp
 *
 *  Created on: 30 avr. 2012
 *      Author: Koudja
 */

#include "NodeQueueItem.h"

NodeQueueItem::NodeQueueItem(Node* node) {
	this->node = node;

	this->previous = NULL;
	this->next = NULL;
}

NodeQueueItem::~NodeQueueItem() {

}


Node* NodeQueueItem::getNode() {
	return this->node;
}

void NodeQueueItem::setPrevious(NodeQueueItem* previous) {
	this->previous = previous;
}
NodeQueueItem* NodeQueueItem::getPrevious() {
	return this->previous;
}


void NodeQueueItem::setNext(NodeQueueItem* next) {
	this->next = next;
}
NodeQueueItem* NodeQueueItem::getNext() {
	return this->next;
}
