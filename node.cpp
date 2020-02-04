#include "node.h"

Node::Node(char data) {
	this.data = data;
}

Node::~Node() {
}

char Node::getData() {
	return data;
}

Node* Node::getNext() {
	return next;
}

Node* Node::getPrevious() {
	return previous;
}

void Node::setNext(Node* node) {
	next = node;
}

void Node::setPrevious(Node* node) {
	previous = node;
}
