#include <iostream>
#include <algorithm>
#include <string>
#include "Node.h"

using namespace std;

// Default constructor
Node::Node():next(nullptr) {} // remember to initialize next to nullptr

// Parameterized constructor
Node::Node(string id, int year, int month, double temperature): id(id), year(year), month(month), temperature(temperature), next(nullptr) {}
// remember to initialize next to nullptr

bool Node::operator<(const Node& b) {

	if (this->id < b.id) {
		return true;
	}
	else if (this->id == b.id) {
		if (this->year < b.year) {
			return true;
		}
		else if (this->year == b.year) {
			if (this->month < b.month) {
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

}
