/*
 * Emma Shu, 2/14/20: The node class is used for a doubly linked list
 * for the binary expression tree but is also utilized for the stack and
 * queue linked lists.
 */

#include <iostream>

using namespace std;

class Node {
	public:
		Node(char data);
		~Node();
		char getData();
		Node* getNext();
		Node* getPrev();
		void setNext(Node* node);
		void setPrev(Node* node);
	private:
		Node* previous;
		Node* next;
		char data;
};	
