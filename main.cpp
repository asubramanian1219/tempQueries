#include "TemperatureDatabase.h"

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char** argv) {

	/*
	if (argc < 3) {
	cout << "Usage: " << argv[0] << " data_file query_file" << endl;
	return 1;
	} else {
	TemperatureDatabase database;
	database.loadData(argv[1]);
	database.performQuery(argv[2]);
	}
	system("pause");
	*/
	TemperatureDatabase database;

	database.loadData("temps-7lines.dat");
    database.performQuery("queries.dat");
	system("pause");
}
