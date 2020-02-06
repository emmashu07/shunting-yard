#include "node.h"

Node::Node(char data) {
	this->data = data;
	previous = NULL;
	next = NULL;
}

Node::~Node() {
	//previous -> next = next;
	//next -> previous = previous;
}

char Node::getData() {
	return data;
}

Node* Node::getNext() {
	return next;
}

Node* Node::getPrev() {
	return previous;
}

void Node::setNext(Node* node) {
	next = node;
}

void Node::setPrev(Node* node) {
	previous = node;
}
