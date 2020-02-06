#include <iostream>
#include <cstring>
#include <cctype>
#include "node.h"

using namespace std;

void push(Node* &stackHead, char data);
void pop(Node* &stackHead);
//Node* peek(Node* stackHead);

int main() {
	Node* stackHead = NULL;
	char input[20];
	bool running = true;

	while (running) {
		cout << "Enter push or pop." << endl;
		cin.get(input, 20);
		cin.ignore(20, '\n');
		for (int i = 0; i < strlen(input); i++) {
			input[i] = toupper(input[i]);
		}
		
		if (strcmp(input, "PUSH") == 0) {
			char charInput;
			cout << "Enter char" << endl;
			cin >> charInput;
			cin.ignore();
			push(stackHead, charInput);
		}
		else if (strcmp(input, "POP") == 0) {
			pop(stackHead);
		}
		else if (strcmp(input, "QUIT") == 0) {
			running = false;
		}
		
		if (stackHead) {
			cout << stackHead -> getData() << endl;
		}
		else {
			cout << "Nothing is in the list!" << endl;
		}
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
		cout << "Nothing is in the list!";
	}
}
