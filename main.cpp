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

int main() {
	Node* stackHead = NULL;
	Node* queueHead = NULL;
	char* original = new char[100];
	char* postfix = new char[100];
	char input[100];

	cout << "Enter a mathematical expression: ";
	cin.get(original, 100);
	cin.ignore(100, '\n');
	postfix = translate(original, stackHead, queueHead);
	cout << "Postfix: " << postfix << endl;
	
	cout << "Enter prefix, postfix, or infix: ";
	cin.get(input, 20);
	cin.ignore(20, '\n');	

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

	// Failed algorithm.

	/*for(int i = 0; i < strlen(input); i++) {
		if (!(isspace(input[i]))) {
			char sHead = peek(stackHead);
			if (isdigit(input[i])) {
				enqueue(queueHead, input[i]);
			}
			else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^') {
				if (sHead == '+' || sHead == '-') {
					if ((input[i] == '+' || input[i] == '-') && sHead != '(') {
						enqueue(queueHead, sHead);
						push(stackHead, input[i]);
						sHead = peek(stackHead);
					}
					else {
						push(stackHead, input[i]);
					}
				}
				else if (sHead == '*' || sHead == '/' || sHead == '^') {
					if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') || sHead != '(') {
						enqueue(queueHead, input[i]);
					}
					else {
						push(stackHead, input[i]);
					}
				}
				else if (sHead == '(') {
					push(stackHead, input[i]);
				}
				else if (!stackHead) {
					push(stackHead, input[i]);
				}
			}
			else if (input[i] == '(') {
				push(stackHead, input[i]);
			}
			else if (input[i] == ')') {
				while (sHead != '(') {
					sHead = peek(stackHead);
					enqueue(queueHead, sHead);
					pop(stackHead);
				}
				pop(stackHead);
			}

		}
	}
	while (stackHead) {
		enqueue(queueHead, peek(stackHead));
		pop(stackHead);
	}
	int num = 0;
	while (queueHead) {
		postfix[num] = peek(queueHead);
		dequeue(queueHead);
		num++;
	}
	postfix[num] = '\0';
	cout << postfix << endl;*/	

	// Testing if all functions had worked for stack and queue.

	/*cout << "Enter push, pop, peek, enqueue, or dequeue." << endl;
	cin.get(input, 20);
	cin.ignore(20, '\n');
	for (int i = 0; i < strlen(input); i++) {
		input[i] = toupper(input[i]);
	}
	
	if (strcmp(input, "PUSH") == 0 || strcmp(input, "ENQUEUE") == 0) {
		char charInput;
		cout << "Enter a character." << endl;
		cin >> charInput;
		cin.ignore();
		if (strcmp(input, "PUSH") == 0) {
			push(stackHead, charInput);
		}
		else {
			enqueue(queueHead, charInput);
		}
	}
	else if (strcmp(input, "POP") == 0) {
		pop(stackHead);
	}
	else if (strcmp(input, "DEQUEUE") == 0) {
		dequeue(queueHead);
	}
	else if (strcmp(input, "PEEK") == 0) {
		cout << "Queue head: " << peek(queueHead) << endl;
		cout << "Stack head: " << peek(stackHead) << endl;
	}*/

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
	char* postfix = new char[100];
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

void printPrefix(Node* stackHead) {
	if (stackHead) {
		cout << peek(stackHead) << ' ';
		printPrefix(stackHead -> getLeft());
		printPrefix(stackHead -> getRight());
	}
}

void printPostfix(Node* stackHead) {
	if (stackHead) {
		printPostfix(stackHead -> getLeft());
		printPostfix(stackHead -> getRight());
		cout << peek(stackHead) << ' ';
	}

}

