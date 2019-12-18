// Name: Matthias Baur
// File Name: prog2.cpp
// Date: 20 November, 2019

// This program simulates a Nondeterministic Pushdown Automata (NPDA) that accepts strings (in the form of passwords) where
// each password may only contain the symbols a, b, 0, 1 and the following conditions hold:
//  1: there must be at least one digit.
//  2: there must be more letters than digits.

// Since a property of NPDAs is that they can accept an empty string as input, this program will use the symbol * to denote an empty string.
// A further logical stipulation is that, since * denotes an empty string, it cannot appear in a string containing any additional characters.

// The NPDA itself is defined as a class called NPDA.
// This class contains all of the functions and data structures required to process input strings.
// It also has additional informative functions to print the instantaneous descriptions of the NPDA, get the stack contents, display whether or not the string was accepted, etc.

// This program consists of 3 source code files and a singular input file that defines the NPDA.
// The files are as follows:

// 1: prog2.cpp
// This file contains the "driver" of the program. It performs the following functions:
// - it accepts the user-provided NPDA defining text file as a command line argument.
// - via the defineNPDATransitionsAndStates() function, it parses the NPDA defining text file and, through the functions of the NPDA class, defines the NPDA transition function.
// - via a loop in main(), it continuously prompts the user to provide strings/passwords to process with the NPDA.
// - via the validatePasswordAlphabet() function, it validates the alphabet of the user-provided password/string -- invalid alphabets will result in descriptive error message and subsequent termination of the program.
// - passwords with valid alphabets will be given to the NPDA class for processing in the validatePasswordWithNPDA() function -- the NPDA class is responsible for displaying instantaneous descriptions and the final result.

// 2: NPDA.h
// This is the header file of the NPDA class used in this program.

// 3: NPDA.cpp
// This is the source file for the NPDA header file used in this program.
// In this file all of the functions for the NPDA class are defined.

// 4: The transition defining file
// This file must be a text file of some name and some file extension.
// The file must be in the current working directory of the executable of this program.

// A template format of the file is as follows:
/*
    *initial_state*
    *final_state_1* *final_state_2* *final_state_3*
    *transition_1*
    *transition_2*
    .
    .
    .
    *transition_n*
*/

// A short example is as follows:
/*
    q_0
    q_6 q_0
    q_0 a z q_1 1z
    q_0 a z q_2 1z
    q_1 a 1 q_3 11
    q_2 a 1 q_4 11
    q_3 a 1 q_5 11
    q_4 a 1 q_6 11
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <utility>

#include "NPDA.h"

using namespace std;

void validatePasswordAlphabet(string);
void validatePasswordWithNPDA(string, NPDA*);
void defineNPDATransitionsAndStates(char* [], NPDA*);

int main(int argc, char* argv[])
{
    // Conditional check to make sure that the user has provided at least two command line arguments (the first being the program executable, the second being the transition function defining file).
	if (argc != 2)
	{
		cout << endl << endl << "Error: " << argc << " command line arguments found -- 2 are required." << endl << endl;

		exit(1);
	}
    
    string password = "";
    
    NPDA npda;
    NPDA* npdaPtr = &npda;
    
    defineNPDATransitionsAndStates(argv, npdaPtr);

    while (true)
    {    
        cout << endl;
        
        cout << "Enter a string to process: ";
        cin >> password;        
        cout << endl;
                
        validatePasswordAlphabet(password);
        validatePasswordWithNPDA(password, npdaPtr);        
    }
    
	return 0;
}

// This function performs the following:
// 1: passes the password to the NPDA class.
// 2: resets the stack of the NPDA class (because a user can successively process passwords).
// 3: calls the processString() function of the NPDA class to begin processing the password.
void validatePasswordWithNPDA(string password, NPDA* npdaPtr)
{       
    npdaPtr->setStringToProcess(password);
    npdaPtr->resetMainStack();    
    npdaPtr->processString();
}

// This function is responsible for validating the alphabetical symbols used for the password (which is provided by the user).
// This is done separately from the NPDA class.
// The valid alphabetical symbols of the NPDA are: {a, b, 0, 1, *}.
// Any symbols that do not match the above set will prompt an error message and subsequent termination of this program.
// The "*" symbol represents the empty string and can therefore not be used with any other symbols in a given password.
void validatePasswordAlphabet(string password)
{
    for (int x = 0; x < password.length(); x++)
    {
        if (password[x] != 'a' && password[x] != 'b' && password[x] != '0' && password[x] != '1' && password[x] != '*')
        {
            cout << "ERROR: The given password used a symbol, \"" << password[x] << "\", that was not in the alphabet of the NPDA." << endl << endl;
            exit(1);
        }
        
        if (password.length() > 1 && password[x] == '*')
        {
            cout << "ERROR: The given password used a symbol, \"" << password[x] << "\", that symbolizes the empty string in an otherwise non-empty string." << endl << endl;
            exit(1);
        }
    }
    
    cout << "Valid password alphabet." << endl << endl;
}

// This function is responsible for reading and parsing the NPDA transition function defining file and appropriately calling the addTransition() function of the NPDA class.
void defineNPDATransitionsAndStates(char* argv[], NPDA* npdaPtr)
{
    ifstream infile;
    
    cout << endl << "File name = " << argv[1] << endl << endl;

    infile.open(argv[1]);

    if (!infile)
    {
        cout << endl << endl << "Could not read file." << endl << endl;

        exit(1);
    }
    
    cout << "Reading transition definitions..." << endl << endl;
    
    bool setInitialState = false;
    bool setFinalStates = false;
        
    while (infile.peek() != EOF && infile.good())
    {               
        if (!setInitialState)   
        {                        

            string initialState = "";            
            infile >> initialState;                    
            npdaPtr->setInitialState(initialState);           
           
            setInitialState = true;
            
            infile >> ws;
        }
        
        else if (!setFinalStates)
        {         
            while (infile.peek() != '\n' && infile.peek() != '\r' && infile.peek() != EOF && infile.good())
            {
                string finalState = "";
                infile >> finalState;
                npdaPtr->addFinalState(finalState);
            }
            
            infile >> ws;
                        
            setFinalStates = true;        
        }
        
        else
        {      
            string transitionComponent = "";            
            vector<string> transitionComponents;
            
            while (infile.peek() != '\n' && infile.peek() != '\r' && infile.peek() != EOF && infile.good())
            {
                string transitionComponent = "";
                infile >> transitionComponent;
                transitionComponents.push_back(transitionComponent);
            }

            infile >> ws;
            
            npdaPtr->addTransition(transitionComponents[0], transitionComponents[1], transitionComponents[2], transitionComponents[3], transitionComponents[4]);            
        }
    }
    
    cout << endl;
    
    infile.close();
}










