// Name: Matthias Baur
// File Name: prog3.cpp
// Date: 1 November, 2017

// This program solves the n-Queens puzzle for n number of queens provided that n >= 1;
// It utilizes a Stack of Nodes where each Node contains an instance of Position as well as a pointer to the next Node.
// Position contains the integer row and column values of a specific queen in the Stack.
// The puzzle itself is solved via a nested loop structure that incrementally builds the solution.
// The program uses a function called confrontation to detect whether there is a
// confrontation between the current queen and the queen to add.
// This is done via an array of Position pointers that holds the positions of
// all the queens currently in the Stack.
// The queen to add is compared to each of the queens in this array.
// If a confrontation is detected, the column position of the queen to add is increased by 1.
// When the column position of the queen to add exceeds the size of the board,
// the algorithm backtracks by popping the current queen off the stack and attempting
// to find a better location for that queen.
// When a solution is found, a table illustrating the solution is printed via the displayResult function.
// "Q" indicates the position of a queen, while "-" indicates an empty position.
// This program uses 3 functions in addition to main().

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <cstdlib> // Standard Library

#include "stack.h"
#include "stack.cpp"

using namespace std;

#ifndef _POSITION
#define _POSITION

// This struct is used to hold the row and column values of a queen.
struct Position
{
	int row, col;
};

#endif

void solvePuzzle(bool &success, bool &failure, int numQueens, Position* board[], Stack<Position> &queens);

bool confrontation(Position p1, Position p2);

void displayResult(int numQueens, Position* board[]);

int main()
{
	int numQueens = 0;

	cout << "Enter the number of queens: ";
	cin >> numQueens;

	if (numQueens < 1)
	{
		cout << endl << endl << "Invalid number of queens.";
		exit(1);
	}

	bool success = false, failure = false;

	Stack<Position> queens;

	Position* board[numQueens];

	for (int y = 0; y < numQueens; y++)
		board[y] = new Position;

	solvePuzzle(success, failure, numQueens, board, queens);

	if (success)
	{
		cout << endl << "Solution found: " << endl << endl;
		displayResult(numQueens, board);
	}

	else
		cout << endl << "No solution." << endl << endl;

	return 0;
}

// This function is responsible for correctly solving the n-Queens problem.
// It utilizes a nested loop structure in combination with the
// confrontation function to evaluate whether there is solution.
// The variable Position* board[] contains the positions of all the queens currently in the stack.
// It is used to compare the queen to add with all the queens in the stack to detect a confrontation.
void solvePuzzle(bool &success, bool &failure, int numQueens, Position* board[], Stack<Position> &queens)
{
	Position queenToAdd;

	queenToAdd.col = queenToAdd.row = 0;

	// Place the initial queen on the Stack.
	queens.push(queenToAdd);

	int numPlacedQueens = 1;

	// Record the initial queen's location.
	board[0]->col = board[0]->row = 0;

	queenToAdd.row = 1;

	// If there is only one queen.
	if (numPlacedQueens == numQueens)
	{
		success = true;
		return;
	}

	bool placedQueen = false, collision = false;

	Position temp;

	int boardIndex = numPlacedQueens-1;

	// This loop is responsible for evaluating the n-Queens problem.
	while (!success && !failure)
	{
		// This variable is used to index the correct position in the board array.
		boardIndex = numPlacedQueens - 1;

		placedQueen = false;

		while (!placedQueen && (queenToAdd.col < numQueens))
		{
			// This loop runs until there are no queens left to compare the queen to add to OR
			// a confrontation is detected.
			while(boardIndex >= 0)
			{
				temp.row = board[boardIndex]->row;
				temp.col = board[boardIndex]->col;

				if (confrontation(temp, queenToAdd))
				{
					collision = true;
					break;
				}

				else
					boardIndex--;
			}

			// If the queen to add has been compared with all other queens
			// in the stack an no confrontation was detected.
			if (collision == false)
			{
				placedQueen = true;
				break;
			}

			collision = false;

			queenToAdd.col++;

			boardIndex = numPlacedQueens - 1;
		}

		if (placedQueen)
		{
			queens.push(queenToAdd);

			board[numPlacedQueens]->row = queenToAdd.row;
			board[numPlacedQueens]->col = queenToAdd.col;

			queenToAdd.row++;
			queenToAdd.col = 0;

			numPlacedQueens++;
		}

		else
		{
			// This conditional is used to correctly deal with the scenario
			// where the last queen on the Stack must be popped.
			if ((numPlacedQueens-1) == 0)
			{
				queens.pop(queenToAdd);

				queenToAdd.col++;

				if (queenToAdd.col > (numQueens - 1))
				{
					failure = true;
					queens.clear();
					break;
				}

				else
				{
					board[0]->row = queenToAdd.row;
					board[0]->col = queenToAdd.col;
				}

				queens.push(queenToAdd);

				queenToAdd.row++;
			}

			else
			{
				queens.pop(queenToAdd);

				queenToAdd.col++;

				numPlacedQueens--;
			}
		}

		if (numPlacedQueens == numQueens)
		{
			success = true;
			return;
		}

		else if (queens.isEmpty())
		{
			failure = true;
			return;
		}
	}
}

// This function is used to detect whether there is a confrontation between two queens.
// It returns true or false depending on the result.
bool confrontation(Position p1, Position p2)
{
	if (p1.col == p2.col)
		return true;

	else if (p1.row == p2.row)
		return true;

	else if (abs(p1.row - p2.row) == abs(p1.col - p2.col))
		return true;

	else
		return false;
}

// This function simply displays the positions of the queens on the board.
void displayResult(int numQueens, Position* board[])
{
	for (int x = 0; x < numQueens; x++)
	{
		int z = board[x]->col;
		int y = 0;

		for (; y != z; y++)
			cout << "-";

		cout << "Q";
		y++;

		for (; y != numQueens; y++)
			cout << "-";

		cout << endl;
	}
}


