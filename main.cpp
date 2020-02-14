#include <iostream>
#include <cstring>
#include <cctype>
#include "node.h"

using namespace std;

void push(Node* &stackHead, char data);
void pop(Node* &stackHead);
void peek(Node* head);
void enqueue(Node* &queueHead, char data);
void dequeue(Node* &queueHead); 
Node* returnTail(Node* queueHead);

int main() {
	Node* stackHead = NULL;
	Node* queueHead = NULL;
	char input[20];
	bool running = true;

	while (running) {
		cout << "Enter a mathematical expression: ";
		cin.get(input, 20);
		cin.ignore(20, '\n');
		for(int i = 0; i < strlen(input); i++) {
			if (!(isspace(input[i]))) {
				if (isdigit(input[i])) {
					enqueue(queueHead, input[i]);
				}
				else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^') {
					if ((stackHead -> getData()) == '+' || (stackHead -> getData()) == '-') {
						if ((input[i] == '+' || input[i] == '-') && (stackHead -> getData()) != '(') {
							enqueue(queueHead, input[i]);
						}
						else {
							push(stackHead, input[i]);
						}
					}
					else if ((stackHead -> getData()) == '*' || (stackHead -> getData()) == '/' || (stackHead -> getData()) == '^') {
						if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') || (stackHead -> getData()) != '(') {
							enqueue(queueHead, input[i]);
						}
						else {
							push(stackHead, input[i]);
						}
					}
				}
				else if (input[i] == '(') {
					push(stackHead, input[i]);
				}
				else if (input[i] == ')') {
					while ((stackHead -> getData()) != '(') {
						enqueue(queueHead, (stackHead -> getData()));
						pop(stackHead);
					}
					pop(stackHead);
				}

			}
		}

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
			cout << "Queue head: ";
			peek(queueHead);
			cout << "Stack head: ";
			peek(stackHead);
		}
		else if (strcmp(input, "QUIT") == 0) {
			running = false;
		}*/
	}

	return 0;
}

void push(Node* &stackHead, char data) {
	if (!stackHead) {
		stackHead = new Node(data);
	}
	else {
		Node* temp = stackHead;
		stackHead = new Node(data);
		stackHead -> setNext(temp);
	}
}

void pop(Node* &stackHead) {
	if (stackHead) {
		Node* temp = stackHead;
		stackHead = stackHead -> getNext();
		delete temp;
	}
	else {
		cout << "Nothing is in the list!" << endl;
	}
}

void peek(Node* head) {
	if (head) {
		cout << head -> getData() << endl;
	}
	else {
		cout << "Nothing to display." << endl;
	}
}

Node* returnTail(Node* queueHead) {
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

void enqueue(Node* &queueHead, char data) {
	Node* tail = returnTail(queueHead);
	Node* newNode = new Node(data);
	if (tail) {
		tail -> setNext(newNode);
	}
	else {
		queueHead = newNode;
	}			
}

void dequeue(Node* &queueHead) {
	if (queueHead) {
		Node* temp = queueHead;
		queueHead = queueHead -> getNext();
		delete temp;
	}
	else {
		cout << "Nothing is in the list!" << endl;
	}
}
