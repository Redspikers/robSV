/*
 * Node.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "Node.h"

Node::Node(int x, int y, bool blocked) {
	this->m_x = x;
	this->m_y = y;
	this->m_cost = 0;
	this->m_parent = NULL;
}
Node::~Node() {

}

void Node::setX(int x) {
	this->m_x = x;
}
int Node::getX() {
	return this->m_x;
}

void Node::setY(int y) {
	this->m_y = y;
}
int Node::getY() {
	return this->m_y;
}

void Node::setCost(int cost) {
	this->m_cost = cost;
}
int Node::getCost() {
	return this->m_cost;
}

void Node::setParent(Node *parent) {
	this->m_parent = parent;
}
Node *Node::getParent() {
	return this->m_parent;
}

void Node::setBlocked(bool blocked) {
	this->m_blocked = blocked;
}

bool Node::isBlocked() {
	return this->m_blocked;
}
