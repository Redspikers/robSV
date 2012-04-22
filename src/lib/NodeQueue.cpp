/*
 * NodeQueue.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "NodeQueue.h"

NodeQueue::NodeQueue() {
	this->data = new Node*[200];
	this->beginning = 0;
	this->end = 0;
	this->count = 0;
}

NodeQueue::NodeQueue(const NodeQueue &otherNodeQueue) {
	this->beginning = otherNodeQueue.beginning;
	this->end = otherNodeQueue.end;
	this->count = otherNodeQueue.count;

	this->data = new Node*[200];
	for (int i = 0; i < 200; i++) {
		this->data[i] = otherNodeQueue.data[i];
	}
}

NodeQueue::~NodeQueue(void) {
	delete[] this->data;
}

void NodeQueue::push(Node *item) {

	this->data[this->end] = item;
	this->end = this->end + 1;
	this->count = this->count + 1;

	if (this->end > 200) {
		this->end -= (200 + 1);
	}
}

Node* NodeQueue::pop(void) {

	Node* result = this->data[this->beginning];
	this->beginning = this->beginning + 1;
	this->count = this->count - 1;

	if (this->beginning > 200) {
		this->beginning -= (200 + 1);
	}

	return result;
}

int NodeQueue::size() {
	return this->count;
}

bool NodeQueue::contains(Node *item) {
	bool result = false;

	int i = this->beginning;

	while(result == false && i <= this->end) {
		if(this->data[i] == item) {
			result = true;
		}
		i++;
	}

	return result;
}

Node* NodeQueue::get(int i) {
	Node* result = NULL;
	if(i >= this->beginning && i <= this->end) {
		result = this->data[i];
	}

	return result;
}

void NodeQueue::remove(Node *item) {
	bool result = false;
	int i = this->beginning;

	while(result == false && i <= this->end) {
		if(this->data[i] == item) {
			result = true;
		}
		i++;
	}
}
