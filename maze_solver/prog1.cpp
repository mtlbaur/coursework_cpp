// Name: Matthias Baur
// File Name: prog1.cpp
// Date: 10 September, 2017

// This program utilizes recursion to attempt to solve a 12 by 12 maze.
// The user must enter the row and column values for the start and end positions of the maze.
// When the a path is located, it is displayed to via a trail of o's beginning at the start position (S)
// and ending at the end position (E).
// If the program does not find a solution to the maze, it will display an appropriate message.
// This program uses four functions in addition to main().

#include <iostream> // Input / Output
#include <iomanip> // Input / Output Manipulation
#include <fstream> // File Stream
#include <cstdlib> // Standard Library

using namespace std;

const int SIZE = 12;

void loadMaze(char maze[][SIZE], char* argv[]);

void getCoordinates(char maze[][SIZE], int &startRow, int &startCol, int &endRow, int &endCol);

void printMaze(char maze[][SIZE], int startRow, int startCol, int endRow, int endCol);

bool findPath(char maze[][SIZE], int startRow, int startCol, int endRow, int endCol);

int main(int argc, char* argv[])
{
	char maze[SIZE][SIZE];

	int startRow, startCol, endRow, endCol;
	
	if (argc != 2)
	{
		cout << endl << endl << "Error: invalid number of command line arguments." << endl << endl;
		exit(1);
	}

	loadMaze(maze, argv);
	
	printMaze(maze, startRow, startCol, endRow, endCol);
	
	getCoordinates(maze, startRow, startCol, endRow, endCol);

	bool x = findPath(maze, startRow, startCol, endRow, endCol);

	// This if statement is responsible for displaying the appropriate maze configuration and ending message
	// depending on whether a solution is found or not.
	if (x == true)
	{	
		maze[startRow][startCol] = 'S';
		maze[endRow][endCol] = 'E';
	
		printMaze(maze, startRow, startCol, endRow, endCol);
	}

	else
	{
		printMaze(maze, startRow, startCol, endRow, endCol);

		cout << endl << "No solution.";
	}

	return 0;
}

// This function is responsible for filling the 2-dimensional array "maze" with the contents of the a text file.
// To read the text file, the file name must be passed to the program via command line arguments.
void loadMaze(char maze[][SIZE], char* argv[])
{
	char x = 0;
	
	ifstream infile;

	infile.open(argv[1]);

	if (!infile)
	{
		cout << endl << endl << "Error: the file could not be read." << endl << endl;

		exit(1);
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			infile.get(x);
			
			maze[i][j] = x;
		}

		infile.ignore(1); // Skips the new line character at the end of a line in the text file.
	}

	infile.close();
}

// This function is responsible for getting the start and end positions in the maze from the user.
void getCoordinates(char maze[][SIZE], int &startRow, int &startCol, int &endRow, int &endCol)
{
	cout << endl << endl << "Enter the row and column positions for the starting location: ";
	cin >> startRow >> startCol;

	cout << endl << endl << "Enter the row and column positions for the ending location: ";
	cin >> endRow >> endCol;

	startRow--;
	startCol--;
	endRow--;
	endCol--;

	cout << endl << endl;
}

// This function simply prints the contents of the 2-dimensional array "maze".
void printMaze(char maze[][SIZE], int startRow, int startCol, int endRow, int endCol)
{
	cout << endl;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << maze[i][j];

		cout << endl;
	}
}

// This function is responsible for solving the maze correctly or detecting when there is no solution.
// It utilizes recursion to systematically explore all four directions from a single point.
// When it encounters a wall or runs out of the bounds of the maze, it returns false and continues 
// the recursive process from the previous function call. 
// If the function locates the end (E), it returns true.
// Otherwise, if the function does not find a solution to the maze, it returns false.
bool findPath(char maze[][SIZE], int startRow, int startCol, int endRow, int endCol)
{
	// This if statement checks whether the function has encountered a wall or has gone out of bounds.
	// If it has, it returns false.
	if ((maze[startRow][startCol] == '*') || (maze[startRow][startCol] == 'o') || (startRow < 0) || (startCol > 11)
			|| (startRow > 11) || (startCol < 0))
		return false;

	// If the solution is found, return true.
	else if (startRow == endRow && startCol == endCol)
		return true;

	maze[startRow][startCol] = 'o'; // Places 'o' characters to leave a trail from the start position to the end position.

	// If one of the recursive calls finds the end and returns true, this statement returns true.
	if (findPath(maze, startRow-1, startCol, endRow, endCol) || findPath(maze, startRow, startCol+1, endRow, endCol) ||
			findPath(maze, startRow+1, startCol, endRow, endCol) || findPath(maze, startRow, startCol-1, endRow, endCol))
		return true;

	// Otherwise, when it has not found a solution, it returns false.
	else
	{
		maze[startRow][startCol] = ' '; // Removes the 'o' characters when it backtracks. 
		return false;
	}
}







