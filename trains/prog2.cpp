// Name: Matthias Baur
// File Name: prog2.cpp
// Date: 3 October, 2017

// This program simulates the switching of train cars in a railway yard.
// It utilizes four linked lists, the first of which - track0 - denotes the initial rail.
// track0 is initialized via the contents of a text file.
// The text file name is passed to the program as a command line argument.
// The three other rails, track1, track2, and track3 take cars from track0 depending on their destination.
// The program outputs the current rail configuration after each switch.
// Once the switching process is done. It outputs a final report of track1, track2, and track3.
// The program allows for two forms of execution denoted by a "-u" or "-o" as command line arguments.
// The former builds the initial linked list in an unordered fashion - as determined by the input text file.
// The latter builds the initial linked list in ascending order depending on the weight of each car.

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <fstream> // File Stream
#include <cstdlib> // Standard Library
#include <string> // Allows use of C++ strings
#include <string.h> // String Handling
#include <cctype> // Allows use of isspace and etc.

#include "train.h"

using namespace std;

void readFile(char* argv[], TrainCar* &track0);

int main(int argc, char* argv[])
{
	// Checks to make sure the number of command line arguments is correct.
	if (argc != 3)
	{
		cout << endl << endl << "Error: invalid number of command line arguments." << endl << endl;

		exit(1);
	}

	TrainCar* track0 = NULL;
	TrainCar* track1 = NULL;
	TrainCar* track2 = NULL;
	TrainCar* track3 = NULL;

	readFile(argv, track0);

	// The following code is responsible for correctly executing train car switching simulation.
	// It utilizes functions from "train.cpp".
	cout << "Track0: ";
	displayTrain(track0);

	cout << endl << "Total weight: ";
	printTrainWeight(track0);

	cout << endl << endl << "Switching begins:" << endl;

	while (track0 != NULL)
	{
		if (track0->destination == "Roanoke")
		{
			switchTrains(track0, track1);
		}

		else if (track0->destination == "Portsmouth")
		{
			switchTrains(track0, track2);
		}

		else
		{
			switchTrains(track0, track3);
		}

		cout << endl << "Track0: ";
		displayTrain(track0);

		cout << endl << "Track1: ";
		displayTrain(track1);

		cout << endl << "Track2: ";
		displayTrain(track2);

		cout << endl << "Track3: ";
		displayTrain(track3);

		cout << endl;
	}

	cout << endl << "Final: " << endl;

	cout << endl << "Track1: ";
	displayTrain(track1);

	cout << endl << "Total weight: ";
	printTrainWeight(track1);

	cout << endl << "Track2: ";
	displayTrain(track2);

	cout << endl << "Total weight: ";
	printTrainWeight(track2);

	cout << endl << "Track3: ";
	displayTrain(track3);

	cout << endl << "Total weight: ";
	printTrainWeight(track3);

	return 0;
}

// This function is responsible for evaluating which fashion in which to order the list.
// It opens the file passed to it from the command line and reads the contents into the
// initial linked list (track0) line by line.
// If the third command line argument is not one of the listed commands, then it displays an error message and exits.
void readFile(char* argv[], TrainCar* &track0)
{
	ifstream infile;

	infile.open(argv[1]);

	if (!infile)
	{
		cout << endl << endl << "Could not read file." << endl << endl;

		exit(1);
	}

	TrainCar* newCar;

	// If the list should be built unordered.
	if (strcmp(argv[2], "-u") == 0)
	{
		while (infile.peek() != EOF)
		{
			newCar = new TrainCar;

			infile >> newCar->id;

			infile >> newCar->contents;

			infile >> newCar->weight;

			infile >> newCar->origin;

			infile >> newCar->destination;

			infile >> ws;

			newCar->next = NULL;

			addToEnd(track0, newCar);
		}
	}

	// If the list should be built ordered.
	else if (strcmp(argv[2], "-o") == 0)
	{
		while (infile.peek() != EOF)
		{
			newCar = new TrainCar;

			infile >> newCar->id;

			infile >> newCar->contents;

			infile >> newCar->weight;

			infile >> newCar->origin;

			infile >> newCar->destination;

			infile >> ws;

			newCar->next = NULL;

			addInAscendingWeight(track0, newCar);
		}
	}

	// If the command line argument was invalid.
	else
	{
		cout << endl << endl << "The third command line argument was invalid." << endl << endl;

		exit(1);
	}

	newCar = NULL;

	infile.close();
}
