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
