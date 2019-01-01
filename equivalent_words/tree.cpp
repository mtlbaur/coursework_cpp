// Name: Matthias Baur
// File Name: tree.cpp
// Date: 29 November, 2017

// This is the source file for the header file "tree.h".

#include "tree.h"

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation

using namespace std;

Tree::Tree()
{
	root = NULL;
}

Tree::~Tree()
{
	performDestroy(root);
}

// This function serves to pass the root pointer to the function that will
// insert the English and Latin words into the tree.
void Tree::insert(string englishWord, string latinWord)
{
	performInsert(root, englishWord, latinWord);
}

// This function is responsible for building the binary search tree such that the
// contents can be displayed in alphabetical order.
// The Latin equivalents are stored in a List object that each node contains via
// List's addToEnd function.
void Tree::performInsert(TreeNode* &root, string englishWord, string latinWord)
{
	if (root == NULL)
	{
		TreeNode* newTreeNode = new TreeNode();
		newTreeNode->englishWord = englishWord;
		newTreeNode->latinEquivalents.addToEnd(latinWord);
		newTreeNode->left = newTreeNode->right = NULL;
		root = newTreeNode;
	}

	else if (englishWord == root->englishWord)
		root->latinEquivalents.addToEnd(latinWord);

	else if (englishWord < root->englishWord)
		performInsert(root->left, englishWord, latinWord);

	else if (englishWord > root->englishWord)
		performInsert(root->right, englishWord, latinWord);
}

// This function serves to pass the root pointer to the function that will display the contents of the tree.
void Tree::display()
{
	performDisplay(root);
}

// This function utilizes inorder traversal to display the contents of the tree in alphabetical order.
void Tree::performDisplay(TreeNode* root)
{
	if (root != NULL)
	{
		performDisplay(root->left);

		cout << root->englishWord << ": ";
		root->latinEquivalents.display();

		performDisplay(root->right);
	}
}

// This function serves to pass the root pointer to the function that will destroy the tree.
void Tree::destroy()
{
	performDestroy(root);
}

// This function utilizes postorder traversal to destroy the Tree.
// Before a node is deleted, the list object's destroy function is called.
void Tree::performDestroy(TreeNode* &root)
{
	if (root != NULL)
	{
		performDestroy(root->left);

		performDestroy(root->right);

		root->latinEquivalents.destroy();

		delete root;
	}
}


