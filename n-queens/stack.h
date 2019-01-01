// Name: Matthias Baur
// File Name: stack.h
// Date: 1 November, 2017

// This is the header file for the source file "stack.cpp".

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <cstdlib> // Standard Library

using namespace std;

#ifndef _STACK
#define _STACK

template <class T>
struct Node
{
	T data;

	Node<T>* next;
};

template <class T>
class Stack
{
private:
	Node<T>* top;

public:
	Stack();
	~Stack();
	void clear();
	bool push(T);
	bool pop(T &);
	bool isEmpty();
};

#endif
