#include "node.h"

Node::Node(char data) {
	this->data = data;
	next = NULL;
	left = NULL;
	right = NULL;
}

Node::~Node() {
}

char Node::getData() {
	return data;
}

Node* Node::getNext() {
	return next;
}

void Node::setNext(Node* node) {
	next = node;
}

void Node::setRight(Node* node) {
	right = node;
}

Node* Node::getRight() {
	return right;
}

void Node::setLeft(Node* node) {
	left = node;
}

Node* Node::getLeft() {
	return left;
}

