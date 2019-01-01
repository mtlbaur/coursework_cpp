// Programmer: Matthias Baur

// File Name: prog2.cpp

// Date of Last Modification: 9/30/2016

/*
 * This program reads the text file "plain.txt" and copies its contents to the array "message".
 * It then takes this array and stores three different encryptions of the contents into three new arrays
 * called "caesarMessage", "atbashMessage", and "reverseMessage".
 * The contents of each of these three arrays are then output to the files "cipher1.txt", "cipher2.txt", and "cipher3.txt", respectively.
 * It uses four functions in addition to main().
 */


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


void readFile(char message[], int &count);

void getCaesarCipher(const char message[], int count);

void getAtbashCipher(const char message[], int count);

void getReverseCipher(const char message[], int count);


const int SIZE = 120;


int main()
{
	char message[SIZE];

	int count = 0;


	for (int x = 0; x < SIZE; x++)
	{
		message[x] = '\0';
	}


	readFile(message, count);

	getCaesarCipher(message, count);

	getAtbashCipher(message, count);

	getReverseCipher(message, count);


	return 0;
}


// This function fills the array "message" with the contents of "plain.txt"
// and simultaneously uses "count" to accumulate the number of characters copied.
// The variable "count" is later used to terminate the encryption loops.
void readFile(char message[], int &count)
{
	char ch;

	int i = 0;


	cout << "Beginning process." << endl << endl;


	ifstream infile;

	infile.open("plain.txt");

	if (!infile)
	{
		infile.clear();

		cout << "Error: \"plain.txt\" could not be read." << endl << endl;

		exit(1);
	}


	ch = infile.peek();

	while (i < SIZE && ch != EOF && infile.good())
	{
		infile.get(ch);

		message[i] = ch;

		i++;

		count++;

		ch = infile.peek();
	}

	infile.close();


	cout << "Copied \"plain.txt\" successfully." << endl << endl;
}


// This function encrypts the contents of array "message" and stores the result in the new array "caesarMessage".
// The encryption takes each letter - it ignores spaces and new line - and shifts them by 13 letters.
// If the shift exceeds the letter 'Z', it will loop back to the beginning of the alphabet.
// For example the letter 'V' would become 'I'.
// The variable "count" is used to stop the loop when the encryption is complete.
// After encryption the new array is output to the file "cipher1.txt".
void getCaesarCipher(const char message[], int count)
{
	int i = 0;

	char caesarMessage[SIZE];


	for (int x = 0; x < SIZE; x++)
	{
		caesarMessage[x] = '\0';
	}


	// This loop is responsible for the encryption process.
	while (i < count && message[i] != EOF)
	{
		if (message[i] != 32 && message[i] != 10)
		{
			if (message[i] + 13 > 90)
			{
				caesarMessage[i] = (64 + ((message[i] + 13) - 90));

				i++;
			}

			else
			{
				caesarMessage[i] = (message[i] + 13);
				i++;
			}
		}

		else
		{
			caesarMessage[i] = message[i];
			i++;
		}
	}


	ofstream outfile("cipher1.txt");

	if (!outfile)
	{
		outfile.clear();

		cout << "Error: \"cipher1.txt\" could not be output.";

		exit(1);
	}

	outfile << caesarMessage;

	outfile.close();


	cout << "Encrypted \"plain.txt\" and created \"cipher1.txt\"." << endl << endl;
}


// This function encrypts the contents of array "message" and stores the result in the new array "atbashMessage".
// The encryption consists of swapping each letter with the corresponding letter of the reversed alphabet.
// For example 'A' would become 'Z', 'E' would become 'V', and so forth.
// The variable "count" is used to stop the loop when the encryption is complete.
// After encryption the new array is output to the file "cipher2.txt".
void getAtbashCipher(const char message[], int count)
{
	char atbashMessage[SIZE];

	int i = 0;

	for (int x = 0; x < SIZE; x++)
	{
		atbashMessage[x] = '\0';
	}


	// This loop is responsible for the encryption process.
	while (i < count && message[i] != EOF)
	{
		if (message[i] != 32 && message[i] != 10)
		{
			atbashMessage[i] = (90 - (message[i] - 65));
			i++;
		}

		else
		{
			atbashMessage[i] = message[i];
			i++;
		}
	}


	ofstream outfile("cipher2.txt");

	if (!outfile)
	{
		outfile.clear();

		cout << "Error: \"cipher2.txt\" could not be output.";

		exit(1);
	}

	outfile << atbashMessage;

	outfile.close();


	cout << "Encrypted \"plain.txt\" and created \"cipher2.txt\"." << endl << endl;
}


// This function encrypts the contents of array "message" and stores the result in the new array "reverseMessage".
// The encryption process consists of taking each whole word and reversing the order of the letters
// without altering the placement of the spaces and new line.
// For example the word "IDEA" would be converted to "AEDI".
// The variable "count" is used to stop the loop when the encryption is complete.
// After encryption the new array is output to the file "cipher3.txt".
void getReverseCipher(const char message[], int count)
{
	char reverseMessage[SIZE];

	int i = 0, j = 0, start = 0, end = 0;


	for (int x = 0; x < SIZE; x++)
	{
		reverseMessage[x] = '\0';
	}


	// This loop is responsible for the encryption process.
	while (i <= count && j <= count && message[i] != EOF)
	{
		if (message[i] == 32 || message[i] == 10 || message[i] == '\0')
		{

			reverseMessage[i] = message[i];

			end = i - 1;

			while (end >= start)
			{
				reverseMessage[j] = message[end];

				j++;

				end--;
			}

			start = i + 1;

			j = start;
		}

		i++;
	}


	ofstream outfile("cipher3.txt");

	if (!outfile)
	{
		outfile.clear();

		cout << "Error: \"cipher3.txt\" could not be output.";

		exit(1);
	}

	outfile << reverseMessage;

	outfile.close();


	cout << "Encrypted \"plain.txt\" and created \"cipher3.txt\"." << endl << endl << "Done." << endl << endl;
}
