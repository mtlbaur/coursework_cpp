// Name: Matthias Baur
// File Name: train.cpp
// Date: 3 October, 2017

// This is the source file for the header file "train.h".

#include "train.h"

using namespace std;

// This function is responsible for adding a car the the end of a train.
void addToEnd(TrainCar* &head, TrainCar* carToAdd)
{
	if (head == NULL)
	{
		head = carToAdd;
		head->next = NULL;
	}

	else
	{
		TrainCar* preCar = findEnd(head);

		preCar->next = carToAdd;
		preCar->next->next = NULL;

		preCar = NULL;
	}
}

// This function is responsible for adding a car to the beginning of a train.
void addToBeginning(TrainCar* &head, TrainCar* carToAdd)
{
	carToAdd->next = head;
	head = carToAdd;
}

// This function is responsible for adding a car in the correct spot in a train.
// The correct spot is determined by weight - it is sorted into ascending order.
// It utilizes the weight_findCar and addToBeginning functions.
void addInAscendingWeight(TrainCar* &head, TrainCar* carToAdd)
{
	 TrainCar* preCar = weight_findCar(head, carToAdd); // Finds the car after which to add the new car.

	 if (preCar == NULL)
		 addToBeginning(head, carToAdd);
	 else
	 {
		 carToAdd->next = preCar->next;
		 preCar->next = carToAdd;
	 }
}

// This function is responsible for switching a car from one train to another.
// It utilizes the addToBeginning functions.
void switchTrains(TrainCar* &srcHead, TrainCar* &dstHead)
{
	TrainCar* switchCar = srcHead;

	if (switchCar != NULL)
	{
		srcHead = srcHead->next;

		addToBeginning(dstHead, switchCar);
	}

	switchCar = NULL;
}

// This functions simply displays a the current configuration of a train.
void displayTrain(TrainCar* head)
{
	TrainCar* walker = head;

	while(walker != NULL)
	{
		cout << walker->id;

		if (walker->next != NULL)
			 cout << "->";

		walker = walker->next;
	}

	walker = NULL;
}

// This function simply displays the weight of a train.
void printTrainWeight(TrainCar* head)
{
	float totalWeight = 0;

	TrainCar* walker = head;

	while(walker != NULL)
	{
		totalWeight += walker->weight;

		walker = walker->next;
	}

	cout << totalWeight;

	walker = NULL;
}

// This function returns the location of the last car in a train.
TrainCar* findEnd(TrainCar* head)
{
	TrainCar* walker = head;

	if (walker == NULL)
		return walker;

	else
	{
		while(walker->next != NULL)
			walker = walker->next;

		return walker;
	}
}

// This function returns the car after which to add the new car.
// It is integral to the addInAscendingWeight() function.
TrainCar* weight_findCar(TrainCar* head, TrainCar* carToAdd)
{
	bool found = false;

	TrainCar* walker = head;

	TrainCar* preCar = NULL;

	while (!found)
	{
	    if (walker == NULL)
	        found = true;

	    else if (walker->weight > carToAdd->weight)
	        found = true;

	    else
		{
	    	preCar = walker;
	    	walker = walker->next;
		}
	}

	walker = NULL;

	return preCar;
}
