// Name: Matthias Baur
// File Name: tree.h
// Date: 29 November, 2017

// This is the header file for the source file "tree.cpp".

#ifndef _TREE
#define _TREE

#include "list.h"

#include <string> // Allows use of C++ strings

using namespace std;

struct TreeNode
{
	string englishWord;

	List latinEquivalents;

	TreeNode* left;
	TreeNode* right;
};

class Tree
{
private:
	TreeNode* root;

public:
	Tree();
	~Tree();
	void insert(string, string);
	void performInsert(TreeNode* &, string, string);
	void display();
	void performDisplay(TreeNode*);
	void destroy();
	void performDestroy(TreeNode* &);
};

#endif

