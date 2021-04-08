/*
 * Emma Shu, 2/14/20: Shunting yard is an algorithm that will translate from an infix
 * mathematical expression to a postfix expression.
 */

#include <iostream>
#include <cstring>
#include <cctype>
#include "node.h"

using namespace std;

void push(Node* &stackHead, char data);
void pop(Node* &stackHead);
char peek(Node* head);
void enqueue(Node* &queueHead, char data);
void dequeue(Node* &queueHead); 
Node* returnTail(Node* queueHead);
int returnPrecedence(char operate);
char* translate(char* input, Node* &stackHead, Node* &queueHead);
void makeTree(char* postfix, Node* &stackHead);
void printPrefix(Node* stackHead);
void printPostfix(Node* stackHead);
void printInfix(Node* stackHead);
void destroyTree(Node* stackHead);

const int MAX_CHAR = 100;

int main() {
	Node* stackHead = NULL;
	Node* queueHead = NULL;
	char* original = new char[MAX_CHAR];
	char* postfix;
	char input[MAX_CHAR];

	cout << "Enter a mathematical expression: ";
	cin.get(original, MAX_CHAR);
	cin.ignore(MAX_CHAR, '\n');
	postfix = translate(original, stackHead, queueHead);
	cout << "Postfix: " << postfix << endl;
	
	cout << "Enter prefix, postfix, or infix: ";
	cin.get(input, MAX_CHAR);
	cin.ignore(MAX_CHAR, '\n');	

	makeTree(postfix, stackHead);
	
	for (int i = 0; i < strlen(input); i++) {
		input[i] = toupper(input[i]);
	}

	if (strcmp(input, "PREFIX") == 0) {
		printPrefix(stackHead);
		cout << endl;
	}
	else if (strcmp(input, "POSTFIX") == 0) {
		printPostfix(stackHead);
		cout << endl;
	}
	else if (strcmp(input, "INFIX") == 0) {
		printInfix(stackHead);
		cout << endl;
	}
	destroyTree(stackHead);
	delete[] postfix;
	delete[] original;

	return 0;
}

int returnPrecedence(char operate) { // Used during comparison in algorithm.
	if (operate == '^') {
		return 3;
	}
	else if (operate == '*' || operate == '/') {
		return 2;
	}
	else if (operate == '+' || operate == '-') {
		return 1;
	}
	else {
		return -1;
	}
}

void push(Node* &stackHead, char data) { // Add to front of stack.
	if (!stackHead) {
		stackHead = new Node(data);
	}
	else {
		Node* temp = stackHead;
		stackHead = new Node(data);
		stackHead -> setNext(temp);
	}
}

void pop(Node* &stackHead) { // Remove the front of stack.
	if (stackHead) {
		Node* temp = stackHead;
		stackHead = stackHead -> getNext();
		delete temp;
	}
	else {
		cout << "Nothing is in the list!" << endl;
	}
}

char peek(Node* head) { // Return the data of the head of stack or queue.
	if (head) {
		return head -> getData();
	}
}

Node* returnTail(Node* queueHead) { // Used for enqueue.
	if (queueHead) {
		if (!(queueHead -> getNext())) {
			return queueHead;	
		}
		else {
			returnTail(queueHead -> getNext());
		}
	}
	else {
		return NULL;
	}
}

void enqueue(Node* &queueHead, char data) { // Add node to the tail of the queue.
	Node* tail = returnTail(queueHead);
	Node* newNode = new Node(data);
	if (tail) {
		tail -> setNext(newNode);
	}
	else {
		queueHead = newNode;
	}			
}

void dequeue(Node* &queueHead) { // Remove node from the front of the stack.
	if (queueHead) {
		Node* temp = queueHead;
		queueHead = queueHead -> getNext();
		delete temp;
	}
	else {
		cout << "Nothing is in the list!" << endl;
	}
}

char* translate(char* input, Node* &stackHead, Node* &queueHead) { // Shunting yard algorithm.
	for (int i = 0; i < strlen(input); i++) {
		if (!isspace(input[i])) {
			if (isdigit(input[i])) { // Is operand.
				enqueue(queueHead, input[i]);
			}
			else if (input[i] == '(') {
				push(stackHead, input[i]);
			}
			else if (input[i] == ')') {
				while (stackHead && peek(stackHead) != '(') {
					char sHead = peek(stackHead);
					pop(stackHead);
					enqueue(queueHead, sHead);
				}
				if (peek(stackHead) == '(') {
					pop(stackHead);
				}
			}
			else { // Is operator.
				while (stackHead && returnPrecedence(input[i]) <= returnPrecedence(peek(stackHead))) {
					if (returnPrecedence(input[i]) == returnPrecedence(peek(stackHead)) && input[i] == '^') {
						break;
					} // Right associative.
					char sHead = peek(stackHead);
					pop(stackHead);
					enqueue(queueHead, sHead);
				}
				push(stackHead, input[i]);
			}	
		}
 
	}
	while (stackHead) { // Empty stack into queue.
		char sHead = peek(stackHead);
		pop(stackHead);
		enqueue(queueHead, sHead);
	}
	char* postfix = new char[MAX_CHAR];
	int num = 0;
	while (queueHead) { // Empty queue into a char array.
		char qHead = peek(queueHead);
		dequeue(queueHead);
		postfix[num] = qHead;
		postfix[num+1] = ' ';
		num += 2;
	}
	postfix[num] = '\0';
	return postfix;	
}

void makeTree(char* postfix, Node* &stackHead) { // Create binary expression tree.
	for (int i = 0; i < strlen(postfix); i++) {
		if (isdigit(postfix[i])) { // Is operand.
			push(stackHead, postfix[i]);
		}
		else {
			if (!isspace(postfix[i])) { // Is operator.
				Node* left = new Node(peek(stackHead));
				left -> setLeft(stackHead -> getLeft());
				left -> setRight(stackHead -> getRight()); // Preserve lost pointers.
				pop(stackHead);
				Node* right = new Node(peek(stackHead));
				right -> setRight(stackHead -> getRight());
				right -> setLeft(stackHead -> getLeft());
				pop(stackHead);
				push(stackHead, postfix[i]);
				stackHead -> setLeft(left);
				stackHead -> setRight(right);
			}
		}
	}
}	

void printInfix(Node* stackHead) { // Traverse through with parentheses for PEMAS.
	if (stackHead) {
		if (!isdigit(peek(stackHead))) {
			cout << '(' << ' ';
		}
		printInfix(stackHead -> getLeft());
		cout << peek(stackHead) << ' ';
		printInfix(stackHead -> getRight());
		if (!isdigit(peek(stackHead))) {
			cout << ')' << ' ';
		}
	}
}

void printPrefix(Node* stackHead) { // Print prefix, print before continuing.
	if (stackHead) {
		cout << peek(stackHead) << ' ';
		printPrefix(stackHead -> getLeft());
		printPrefix(stackHead -> getRight());
	}
}

void printPostfix(Node* stackHead) { // Print postfix, print after continuing.
	if (stackHead) {
		printPostfix(stackHead -> getLeft());
		printPostfix(stackHead -> getRight());
		cout << peek(stackHead) << ' ';
	}

}

void destroyTree(Node* stackHead) {
	if (stackHead) {
		destroyTree(stackHead -> getLeft());
		destroyTree(stackHead -> getRight());
		delete stackHead;
	}
}
