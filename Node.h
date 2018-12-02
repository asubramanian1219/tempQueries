#ifndef NODE
#define NODE

// Include the header file for the data struct/class if you use one.
// For example, if you have a data class in data.h, put
//  #include "data.h"
// below.
#include <string>

struct Node {
	// Put your data here. You have 2 options:

	//   * Add your member variable for the data fields here.

	//   * You can use an extra struct/class
	//     for storing the data (e.g. data.cpp).
	//     In that case, put your definition of the data class
	//     in a separate header file (e.g. data.h).

	// Pointer to the next node in the linked list
	Node* next;

	// Default constructor
	Node(); // remember to initialize next to nullptr
	Node(std::string id, int year, int month, double temperature); // remember to initialize next to nullptr

	bool operator<(const Node& b);

  // The function below is written. Do not modify it
	virtual ~Node() {}

	std::string id;
	int year;
	int month;
	double temperature;
};

#endif
