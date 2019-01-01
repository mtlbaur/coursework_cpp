// Name: Matthias Baur
// File Name: list.h
// Date: 29 November, 2017

// This is the header file for the source file "list.cpp".

#ifndef _LIST
#define _LIST

#include <string> // Allows use of C++ strings

using namespace std;

struct ListNode
{
	string latinWord;

	ListNode* next;
};

class List
{
private:
	ListNode* head;

public:
	List();
	~List();
	void addToEnd(string);
	void performAddToEnd(ListNode* &, string);
	void deleteFromBeginning(ListNode* &);
	void display();
	void destroy();
	ListNode* findEnd(ListNode*);
};

#endif
