#include "LinkedList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Node.h"
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr) { return; }

LinkedList::~LinkedList() {
	//cout << "Destructing : " << this->head << endl;

	Node* current = this->head;

	while (current != NULL) {

		Node* deleteNode = current;

		current = current->next;

		delete deleteNode;

	}

}

LinkedList::LinkedList(const LinkedList& source) {

	if (source.head == NULL)
		this->head = NULL;

	else {

		head = new Node(source.head->id, source.head->year, source.head->month, source.head->temperature);
		Node *current = head;
		Node *sourceHead = source.head;
		Node *currentSource = sourceHead;

		while (currentSource->next != NULL) {
			current->next = new Node(currentSource->next->id, currentSource->next->year, currentSource->next->month, currentSource->next->temperature);
			currentSource = currentSource->next;
			current = current->next;
		}
	}

}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	if (this != &source) {
		LinkedList temp(source);
		swap(temp.head, head);

	}
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) {
	Node* n = new Node(location, year, month, temperature);
	Node* temp;
	Node* curr = head;

	if (curr == nullptr) { head = n; tail = n; return; } //Assigns the node as head/tail of the list if the list is empty.

	else {
		while (curr->next != NULL) {
	
			if (*n < *head) {
				n->next = head;
				head = n;
				break;
			}
			else {
				
				if (((*curr < *n) == true) && ((*curr->next < *n) == false)) {
					n->next = curr->next;
					curr->next = n;
					break;
				}
				else
					curr = curr->next;
			}
		}
		if (curr->next == NULL) {
			if (*n < *head) {
				n->next = head;
				head = n;
			}
			else {
				tail->next = n;
				tail = n;
			}
		}

	}

	return;

}

void LinkedList::clear() {
	Node* current = this->head;

	while (current != NULL) {

		Node* deleteNode = current;
		current = current->next;
		delete deleteNode;

	}
	head = nullptr;
	tail = nullptr;
	//return;
}

void LinkedList::print() const {
	/* Do not modify this function */
	print(cout);
}

void LinkedList::print(ostream& os) const {
	/* Do not modify this function */
	os << *this;
}

Node* LinkedList::getHead() {
	return head;

}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	Node* temp = ll.head;
	while (temp != NULL) {
		os << temp->id << " " << temp->year << " " << temp->month << " " << setprecision(10) << temp->temperature << endl;
		temp = temp->next;
	}
	return os;
}
