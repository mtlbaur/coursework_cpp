// Name: Matthias Baur
// File Name: NPDA.cpp
// Date: 20 November, 2019

// This is the source file for the header file "NPDA.h".

#include <iostream>
#include <iomanip>

#include "NPDA.h"

using namespace std;

NPDA::NPDA()
{
    // Set the initial stack top symbol.
    mainStack.push('z');
}

NPDA::~NPDA()
{
}

// This function allows a user to set the string/password to process as a data member of this NPDA class.
void NPDA::setStringToProcess(string stringToProcess)
{ 
    this->stringToProcess = stringToProcess;    
}

// This function allows a user to the initial state of the NPDA.
// This is used in the defineNPDATransitionsAndStates() function of the driver.
void NPDA::setInitialState(string initialState)
{
    cout << "initialState = " << initialState << endl;
 
    currentState = initialState;    
}

// This function allows a user to add final states to the NPDA.
// This is used in the defineNPDATransitionsAndStates() function of the driver.
void NPDA::addFinalState(string finalState)
{
    cout << "finalState = " << finalState << endl;
    
    finalStates.push_back(finalState);
}

// This function allows a user define transitions of the transition function of the NPDA.
// This is used in the defineNPDATransitionsAndStates() function of the driver.
// This function will also, for informative purposes, print the transitions it is defining.
void NPDA::addTransition(string currentState, string inputSymbol, string stackTopSymbol, string nextState, string stackSymbolsToPush)
{    
    cout << "d(" << currentState << ", " << inputSymbol << ", " << stackTopSymbol << ") = {(" << nextState << ", " << stackSymbolsToPush << ")}" << endl;
    
    transitionFunction.insert(pair<tuple<string, string, string>, tuple<string, string>>(tuple<string, string, string>(currentState, inputSymbol, stackTopSymbol), tuple<string, string>(nextState, stackSymbolsToPush)));
}

// A function to reset the mainStack data member of this class by popping its contents and pushing the stack top symbol, "z".
void NPDA::resetMainStack()
{    
    while (!mainStack.empty())
    {
        mainStack.pop();
    }
    
    mainStack.push('z');
}

// This function will update the contents of the mainStack (used in recursive processing) in accord with the current state of the password being processed.
char NPDA::updateStack(string updateString)
{
    char stackTop = mainStack.top();
    
    if (stackTop != 'z')
        mainStack.pop();
    
    if (updateString != "*")
    {
        for (int i = updateString.length() - 1; i >= 0; i--)
        {
            if (updateString.at(i) != 'z')
                mainStack.push(updateString.at(i));
        }
    }     

    return stackTop;
}

// This function is used to undo prior stack updates during recursive processing.
// It directly undoes the operations of the updateStack() function of this NPDA class.
void NPDA::undoStackUpdate(char previousStackTop, string updateString)
{    
    if (updateString != "*")
    {
        for (int i = updateString.length() - 1; i >= 0; i--)
        {
            if (mainStack.top() != 'z')
                mainStack.pop();
        }
    } 

    if (previousStackTop != 'z')
        mainStack.push(previousStackTop);
}

// This function allows the driver to begin the processing of the input string.
// It also displays the final "String accepted." or "String rejected." message that appears after the instantaneous descriptions displayed during processing.
void NPDA::processString()
{
    if (process(currentState, stringToProcess) == true)
        cout << endl << "String accepted." << endl;
    
    else
        cout << endl << "String rejected." << endl;
}

// This is the main recursively-utilized function for processing the input string.
// Herein lies the logic for determining:
// 1: whether or not a final state has been attained.
// 2: whether or not further paths should be processed (this is done via the processAvailablePaths() function called in this class).
// 3: whether or not the entirety of the input string has been processed.
//
// Additionally, this function calls the displayInstantaneousDescription() to provide a user with a description for the processing path of the input string.
// This function, after all recursive options and paths have been explored, will returned either "true" or "false" depending on whether the string was accepted.
// This return value is utilized by processString() to display a conclusionary message for the processing.
bool NPDA::process(string currentState, string stringToProcess)
{    
    displayInstantaneousDescription(currentState, stringToProcess);

    bool atFinalState = false;
    bool noMoreSymbolsToProcess = false;
    
    for (string finalState : finalStates)
    {        
        if (currentState == finalState)
        {            
            atFinalState = true;
        }
    }
    
    if (stringToProcess.length() == 0 || stringToProcess == "*")
    {       
        noMoreSymbolsToProcess = true;
    }
    
    if (atFinalState && noMoreSymbolsToProcess)
    {
        return true;
    }
    
    string symbolToProcess = "";
    string stackTop = "";
         
    if (!noMoreSymbolsToProcess)
    {
         symbolToProcess = stringToProcess.front();    
    }
    
    // If there are no more symbols to process, the symbol to process should be the empty string which, in our case, will be represented as an "*".
    else if (noMoreSymbolsToProcess && symbolToProcess != "*")
    {        
        symbolToProcess = "*";
    }
    
    stackTop = mainStack.top();
        
    pair<multimap<tuple<string, string, string>, tuple<string, string>>::iterator, multimap<tuple<string, string, string>, tuple<string, string>>::iterator> itr;    
    itr = transitionFunction.equal_range(tuple<string, string, string>(currentState, symbolToProcess, stackTop));
        
    // If one of the processed paths returned true, return true.
    if (processAvailablePaths(symbolToProcess, stringToProcess, itr) == true)
        return true;
    
    // If the current symbol to process is the empty string (symbolized by "*"), check for available lambda transitions and process them.
    if (symbolToProcess != "*")
    {
        itr = transitionFunction.equal_range(tuple<string, string, string>(currentState, "*", stackTop));
        
        if (processAvailablePaths("*", stringToProcess, itr) == true)
            return true;
    }
        
    return false;        
}

// This function is used by the processString() function of this class to display the instantaneous description of the input string processing.
void NPDA::displayInstantaneousDescription(string currentState, string stringToProcess)
{    
    if (stringToProcess == "")
        stringToProcess = "*";
    
    cout << "(" << currentState << ", " << stringToProcess << ", " << getStackContents() << ")" << endl;
}

// This function is used by the processString() function of this class to recursively call the process() function on all the available transitions for the current (state, input_symbol, stack_top_symbol) input tuple.
bool NPDA::processAvailablePaths(string symbolToProcess, string stringToProcess, pair<multimap<tuple<string, string, string>, tuple<string, string>>::iterator, multimap<tuple<string, string, string>, tuple<string, string>>::iterator> itr)
{
    // Iterate through each possible transition for the input tuple.
    for (multimap<tuple<string, string, string>, tuple<string, string>>::iterator i = itr.first; i != itr.second; i++)
    {        
        tuple<string, string, string> first = i->first;
        tuple<string, string> second = i->second;

        string nextState = get<0>(second);
        string nextStackContents = get<1>(second);
        string nextStringToProcess = stringToProcess;
        
        // Since we have processed a symbol, remove that symbol from the stringToProcess.
        if (stringToProcess.length() > 0 && symbolToProcess != "*")
            nextStringToProcess.erase(nextStringToProcess.begin());
        
        // Store the previous stack to symbol so as to be able to undo the update operation.
        char previousStackTop = updateStack(nextStackContents);        
                
        cout << "|- ";
        
        // Recursively call process on the next state and input string combiantion to process.
        if (process(nextState, nextStringToProcess) == true)
        {
            return true;
        }

        // If the recursive call to process returned false, undo the stack update since that path has been explored.
        undoStackUpdate(previousStackTop, nextStackContents);       
    }
    
    return false;
}

// This is a utility/informational function to get the current contents of the mainStack data member of this NPDA class.
string NPDA::getStackContents()
{
    string stackContents = "";

    stack<char> tempStack;
    
    char stackTop;
    
    while (!mainStack.empty())
    {
        stackTop = mainStack.top();
        stackContents += stackTop;        
        tempStack.push(stackTop);
        mainStack.pop();
    }
    
    while (!tempStack.empty())
    {
        stackTop = tempStack.top();
        mainStack.push(stackTop);
        tempStack.pop();
    }
    
    return stackContents;
}









