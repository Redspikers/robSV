/*
 * Node.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Node.h"

Node::Node(Cell *cell) {
	this->cell = cell;
	this->parent = NULL;

}
Node::~Node() {

}


void Node::setCost(int cost) {
	this->cost = cost;
}
int Node::getCost() {
	return this->cost;
}

void Node::setParent(Node *parent) {
	this->parent = parent;
}
Node* Node::getParent() {
	return this->parent;
}

Cell* Node::getCell() {
	return this->cell;
}

void Node::setNext(Node* next) {
	this->next = next;
}
Node* Node::getNext() {
	return this->next;
}
