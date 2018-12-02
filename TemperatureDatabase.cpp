#include "TemperatureDatabase.h"

#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "LinkedList.h"
#include "Node.h"
using namespace std;


void TemperatureDatabase::loadData(const string& filename) {

	int currentYear = 2018;

	int count = 0;

	ifstream openFile;

	string id;
	int year;
	int month;
	double temperature;

	openFile.open(filename);

	if (!openFile.is_open()) {
		cout << "Input File doesn't exist" << endl;
	}
		
	else {
		while (!openFile.eof()) {
			openFile >> id;
			openFile >> year;
			openFile >> month;
			openFile >> setprecision(9) >> temperature;

			if ((year >= 1800 && year <= currentYear) && (month >= 1 && month <= 12) && (temperature > -51 && temperature < 51)) {
				records.insert(id, year, month, temperature);
			}
			else if (temperature != -99.99) {
				cout << "Error: Invalid temperature.\n" << endl;

			}
		}
	}

	//openFile.close();
	//return;
}

void TemperatureDatabase::performQuery(const string& filename) {

	ifstream openFile;
	ofstream outFile;

	string station;
	string query;
	int startYear;
	int endYear;
	bool nodeExists = false;

	openFile.open(filename);
	outFile.open("result.dat");

	if (!openFile.is_open()) {
		cout << "Input File doesn't exist" << endl;
	}

	else {
		while (!openFile.eof()) {

			nodeExists = false;
			openFile >> station;
			openFile >> query;
			openFile >> startYear;
			openFile >> endYear;

			if ((startYear > endYear) || (startYear < 1800) ||
				(endYear > 2018)) {
				cout << "Error: Invalid year";
				break;
			}

			else if (query != "AVG" && query != "MODE") {
				cout << "Error: Invalid query";

			}
			Node* startNode = records.getHead();

			while ((startNode != NULL)) {
				if ((startNode->id == station && startNode->year >= startYear && startNode->year <= endYear)) {
					nodeExists = true;
					break;
				}
				startNode = startNode->next;

			}

			if (nodeExists == false) {
				outFile << station << " " << startYear << " " << endYear << " " << query << " unknown" << endl;
			}
			else {
				nodeExists = false;
				Node* endNode = records.getHead();
				while ((endNode != NULL)) {
					if (endNode->next == NULL && (endNode->id == station && endNode->year <= endYear && endNode->year >= startYear)) {
						nodeExists = true;
						break;
					}
					else if ((*startNode<*endNode) && (endNode->next->id != station || endNode->next->year > endYear)) {
						nodeExists = true;
						break;
					}

					endNode = endNode->next;

				}
				if (endNode == NULL) {
					outFile << station << " " << startYear << " " << endYear << " " << query << " unknown" << endl;
				}
				else {
					if (query == "AVG") {
						double sum = 0;
						double numElements = 0;
						while ((startNode != NULL) && (*startNode < *endNode)) {
							sum += startNode->temperature;
							numElements++;
							startNode = startNode->next;
						}
						sum += endNode->temperature;
						numElements++;
						double avg = sum / numElements;
						outFile << station << " " << startYear << " " << endYear << " " << query << " " << avg << endl;


					}
					else if (query == "MODE") {
						vector<int> numbers = {};

						while (startNode != NULL && (*startNode<*endNode)) {

							numbers.push_back(round(startNode->temperature));
							startNode = startNode->next;

						}
						numbers.push_back(round(endNode->temperature));
						sort(numbers.begin(), numbers.end());
						int mode = numbers.at(0);
						int countOld = 0;
						int countNew = 0;
						int i = 0;
						int start = 0;
						while (i < numbers.size()) {
							while ((numbers.at(i) == numbers.at(start)) && i < numbers.size()) {
								countNew++;
								i++;
								if (i == numbers.size())
									break;
							}
							if (countNew >= countOld) {
								mode = numbers.at(i - 1);
								start = i;
								countOld = countNew;
								countNew = 0;
							}
							else {
								start = i;
								countNew = 0;
							}
						}
						outFile << station << " " << startYear << " " << endYear << " " << query << " " << mode << endl;

					}

				}
			}


		}
	}
}

LinkedList TemperatureDatabase::getRecords() {
	return records;
}
