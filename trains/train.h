// Name: Matthias Baur
// File Name: train.h
// Date: 3 October, 2017

// This is the header file for the source file "train.cpp".

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <fstream> // File Stream
#include <cstdlib> // Standard Library
#include <string> // Allows use of C++ strings
#include <cctype> // Allows use of isspace and etc.

using namespace std;

#ifndef _TRAIN
#define _TRAIN

struct TrainCar
{
	string id, contents, origin, destination;

	float weight;

	TrainCar* next;
};

void addToEnd(TrainCar* &, TrainCar*);

void addToBeginning(TrainCar* &, TrainCar*);

void addInAscendingWeight(TrainCar* &, TrainCar*);

void switchTrains(TrainCar* &, TrainCar* &);

void displayTrain(TrainCar*);

void printTrainWeight(TrainCar*);

TrainCar* findEnd(TrainCar*);

TrainCar* weight_findCar(TrainCar*, TrainCar*);

#endif
