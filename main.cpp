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
void translate(char* &input, Node* &stackHead, Node* &queueHead);

int main() {
	Node* stackHead = NULL;
	Node* queueHead = NULL;
	//char original[20];
	char* postfix;
	bool running = true;

	while (running) {
		cout << "Enter a mathematical expression: ";
		cin.get(postfix, 20);
		cin.ignore(20, '\n');
		translate(postfix, stackHead, queueHead);
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
		}
		else if (strcmp(input, "QUIT") == 0) {
			running = false;
		}*/
	}

	return 0;
}

int returnPrecedence(char operate) {
	if (operate == '^') {
		return 3;
	}
	else if (operate == '*' || operate == '/') {
		return 2;
	}
	else if (operate == '+' || operate == '-') {
		return 1;
	}
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

char peek(Node* head) {
	if (head) {
		return head -> getData();
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

void translate(char* &input, Node* &stackHead, Node* &queueHead) {
	for (int i = 0; i < strlen(input); i++) {
		if (!isspace(input[i])) {
			char sHead = peek(stackHead);
			cout << sHead << endl;
			if (isdigit(input[i])) {
				enqueue(queueHead, input[i]);
			}
			else if (input[i] == '(') {
				push(stackHead, input[i]);
			}
			else if (input[i] == ')') {
				while (stackHead && sHead != '(') {
					pop(stackHead);
					enqueue(queueHead, sHead);
					sHead = peek(stackHead);
				}
				sHead = peek(stackHead);
				//cout << sHead << endl;
				if (sHead == '(') {
					cout << "I'm here" << endl;
					pop(stackHead);
				}
			}
			else {
				while (stackHead && returnPrecedence(input[i]) <= returnPrecedence(sHead)) {
					pop(stackHead);
					enqueue(queueHead, sHead);
				}
				push(stackHead, input[i]);
			}	
		}
 
	}
	char sHead = peek(stackHead);
	while (stackHead) {
		pop(stackHead);
		enqueue(queueHead, sHead);
		sHead = peek(stackHead);
	}
	char postfix[20];
	char ch = peek(queueHead);
	int num = 0;
	while (queueHead) {
		dequeue(queueHead);
		postfix[num] = ch;
		ch = peek(queueHead);
		num++;
	}
	postfix[num] = '\0';
	cout << postfix << endl;	
}
