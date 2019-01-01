// Name: Matthias Baur
// File Name: stack.cpp
// Date: 1 November, 2017

// This is the source file for the header file "stack.h".

#include "stack.h"

using namespace std;

template <class T>
Stack<T>::Stack()
{
	top = NULL;
}

template <class T>
Stack<T>::~Stack()
{
	if (top != NULL)
	{
		Node<T>* temp = top;

		while (top != NULL)
		{
			top = top->next;

			delete temp;
			temp = top;
		}
	}
}

// This function allows the manual clearing of the stack.
template <class T>
void Stack<T>::clear()
{
	if (top != NULL)
	{
		Node<T>* temp = top;

		while (top != NULL)
		{
			top = top->next;
			delete temp;
			temp = top;
		}
	}
}

// This function is responsible for add a new node - with the correct data - to the stack.
template <class T>
bool Stack<T>::push(T dataToPush)
{
	if (new Node<T> == NULL)
		return false;

	Node<T>* newNode = new Node<T>;

	newNode->data = dataToPush;

	if (top == NULL)
		newNode->next = NULL;
	else
		newNode->next = top;

	top = newNode;

	return true;
}

// This function is responsible for popping the top queen from the stack provided the stack is not empty.
template <class T>
bool Stack<T>::pop(T &dataToPop)
{
	if (isEmpty())
		return false;

	Node<T>* temp = top;

	dataToPop = top->data;

	top = top->next;

	delete temp;

	return true;
}

// This function checks whether the stack is empty.
template <class T>
bool Stack<T>::isEmpty()
{
	return(top == NULL);
}
