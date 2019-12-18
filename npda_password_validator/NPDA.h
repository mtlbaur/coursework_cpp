// Name: Matthias Baur
// File Name: NPDA.h
// Date: 20 November, 2019

// This is the header file for the source file "NPDA.cpp".

#ifndef _NPDA
#define _NPDA

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <stack>

using namespace std;

class NPDA
{
    private:
        string stringToProcess;
        string currentState;
        vector<string> finalStates;  
        
        // The following mapping function defines the bahavior of the NPDA at a particular (state, input_symbol, stack_top_symbol) tuple for some valid input (valid meaning a symbol in the alphabet).
        multimap<tuple<string, string, string>, tuple<string, string>> transitionFunction;    
        stack<char> mainStack;

    public:
        NPDA();         
        ~NPDA();
        
        // Setter function to set the string (in our case, a password) to process.
        void setStringToProcess(string);
        
        // Setter function to set the initial state of the NPDA.
        void setInitialState(string);
        
        // Function to add final states to the "finalStates" vector data member of this NPDA class.
        void addFinalState(string);
        
        // Function to define transitions to for the multimap "transitionFunction" data member of this NPDA class.
        void addTransition(string, string, string, string, string);

        // Function to pop the whole contents of the mainStack data member of this class and push the stack stop symbol ("z").
        void resetMainStack();
        
        // Function used as part of the recursive processing of passwords to update the mainStack contents in accord with how many symbols have been process from the input string.
        char updateStack(string);
        
        // Function used as part of the recurive processing of passwords to undo a previous stack update (in order to be able to explore other processing paths).
        void undoStackUpdate(char, string);
        
        // This is the main function that starts the processing of the input string. This is called in the driver ("prog2.cpp") of this program.
        void processString();
        
        // This is the primary internal process function used in the recursive processing of the password.
        bool process(string, string);
        
        // This function is used to, during recursive processing, identify and systematically process all available paths should prior paths not result in a acceptance.
        bool processAvailablePaths(string, string, pair<multimap<tuple<string, string, string>, tuple<string, string>>::iterator, multimap<tuple<string, string, string>, tuple<string, string>>::iterator>);
        
        // This is a simple function to display the instantaneous description of the NPDA class.
        void displayInstantaneousDescription(string, string);
        
        // This is an informational function used to get the contents of the mainStack data member of this NPDA class.
        string getStackContents();
};

#endif