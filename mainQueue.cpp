#include "Registrar.h"
#include <iostream>
using namespace std;

// bool method to check if the simulation is complete
bool ShouldKeepGoing(Registrar* reg)
{
    // checking if studentQueue is empty
    if(!reg->studentQueue->isEmpty())
    {
        return true;
    }
    // checking if all the windows are empty
    if(reg->AreAllWindowsEmpty() == false)
    {
        return true;
    }
    return false;

}

// main method
int main(int argc, char** argv)
{
    // checking if user used command line to input an argument
    if(argc <= 1)
    {
        cout << "You didn't enter a file!" << endl;
        return 0;
    }

    // assigning fileName to the first argument of the command line
    string fileName = argv[1];

    int time = 0;
    // variable used to check if simulation is complete
    bool keepGoing = true;
    // creating new registrar object
    Registrar* reg = new Registrar();
    // filling the studentQueue with the students after reading through the inputted file
    reg->FillQueue(fileName);
    // filling the registrar's windows
    reg->FillWindows();

    // assigning currentSize to the studentQueue's size
    int currentSize = reg->studentQueue->getSize();

    // while the simulation is going
    while(keepGoing)
    {
        // calling functions to depopulate, populate, and increment each window's idle time
        reg->DepopulateWindows();
        reg->PopulateWindows(time);
        reg->IncrementTimeIdleForAll();
        // increment time for each iteration
        ++time;
        ++reg->waitTimeVariable;
        // calling on function to check if simulation is done
        keepGoing = ShouldKeepGoing(reg);
        // iterating through all the windows
        for (int i = 0; i < reg->windowsOpen; ++i)
        {
          // decrementing the window's timeBusy variable if it is not 0
          if(reg->windows[i].timeBusy != 0)
          {
            reg->windows[i].timeBusy--;
          }
        }
    }

    // calling on CalculateStats after the simulation is complete 
    reg -> CalculateStats();
    return 0;
}
