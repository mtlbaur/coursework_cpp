// Name: Matthias Baur
// File Name: list.cpp
// Date: 29 November, 2017

// This is the source file for the header file "list.h".

#include "list.h"

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation

using namespace std;

List::List()
{
	head = NULL;
}

List::~List()
{
	while (head != NULL)
	{
		deleteFromBeginning(head);
	}
}

// This function serves to pass the head pointer to the function that will
// add a word to the end of the list.
void List::addToEnd(string dataToAdd)
{
	performAddToEnd(head, dataToAdd);
}

// This function is responsible for adding a word to the end of the list.
void List::performAddToEnd(ListNode* &head, string dataToAdd)
{
	if (head == NULL)
	{
		head = new ListNode;
		head->latinWord = dataToAdd;
		head->next = NULL;
	}

	else
	{
		ListNode* preNode = findEnd(head);

		preNode->next = new ListNode;

		preNode->next->latinWord = dataToAdd;
		preNode->next->next = NULL;

		preNode = NULL;
	}
}

// This function simply deletes the first node in the list.
void List::deleteFromBeginning(ListNode* &head)
{
	ListNode* temp = head;
	head = head->next;
	delete temp;
}

// This function displays the contents of the list.
void List::display()
{
	ListNode* walker = head;

	while(walker != NULL)
	{
		cout << walker->latinWord;

		if (walker->next != NULL)
			 cout << ", ";

		walker = walker->next;
	}

	cout << endl;

	walker = NULL;
}

// This function destroys the list.
void List::destroy()
{
	while (head != NULL)
	{
		deleteFromBeginning(head);
	}
}

// This function returns the last node of the list if the list has at least one node.
// Otherwise, it will return NULL.
ListNode* List::findEnd(ListNode* head)
{
	ListNode* walker = head;

	if (walker == NULL) // Technically unnecessary because performAddToEnd accounts for this.
		return walker;

	else
	{
		while(walker->next != NULL)
			walker = walker->next;

		return walker;
	}
}

