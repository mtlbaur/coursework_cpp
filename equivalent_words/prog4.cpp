// Name: Matthias Baur
// File Name: prog4.cpp
// Date: 29 November, 2017

// This program converts a list of a Latin words with corresponding English equivalents into a list of
// English words with Latin equivalents.
// It utilizes a binary search tree class (Tree) wherein each node contains a string for the English word and
// a linked list class object (List) to hold the Latin equivalents.
// The programs acquires the original list from a text file whose name is entered via the command line.
// The readFile function in the driver file is responsible for parsing the text file.
// It parses the file and inserts the English and Latin words for each line via the Tree class's insert function.
// When the file has been read, the display function is called on the Tree object which utilizes an inorder
// traversal to display the words.
// In order to display the contents of the List object of each Tree node, it calls the List class's display function
// which traverses and displays each word it contains in alphabetical order.

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <fstream> // File Stream
#include <cstdlib> // Standard Library
#include <string> // Allows use of C++ strings
#include <cctype> // Allows use of isspace and etc.

#include "list.h"
#include "tree.h"

using namespace std;

void readFile(char* argv[], Tree &tree);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << endl << endl << "Error: invalid number of command line arguments." << endl << endl;
		exit(1);
	}

	string fileName;

	Tree tree;

	readFile(argv, tree);

	tree.display();

	return 0;
}

// This function is responsible for correctly parsing the contents of the text file and appropriately
// calling Tree's insert function.
void readFile(char* argv[], Tree &tree)
{
	string englishWord = "", latinWord = "", temp = "";

	int pos, size;

	ifstream infile;

	infile.open(argv[1]);

	if (!infile)
	{
		cout << endl << endl << "Error: the file could not be read." << endl << endl;

		exit(1);
	}

	// This loop parses the text file and fills the Tree.
	while (infile.peek() != EOF)
	{
		getline(infile, temp, '\n');

		pos = 0;

		size = temp.size();

		while (temp.at(pos) != ':')
		{
			latinWord += temp.at(pos);
			pos++;
		}

		pos++;
		pos++;

		while (pos < size)
		{
			while (temp.at(pos) != ',')
			{
				englishWord += temp.at(pos);

				pos++;

				if (pos >= size)
					break;
			}

			tree.insert(englishWord, latinWord);

			pos++;
			pos++;

			englishWord = "";
		}

		latinWord = "";
		englishWord = "";
	}
}
