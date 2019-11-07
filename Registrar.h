#include "Window.h"
#include <iostream>

using namespace std;

class Registrar
{
public:
    Registrar(); // constructor for Registrar object

    //PUBLIC METHODS:
    // method to fill the queue with student objects
    void FillQueue(string fileName);
    // method to fill the windows
    void FillWindows();
    // method to populate the open windows with students and takes them out of the studentQueue
    void PopulateWindows(int currentTime);
    // method to depopulate students from windows after they are finished at the registrar
    void DepopulateWindows();
    // method to increment the time idle for all windows
    void IncrementTimeIdleForAll();
    // method that checks if the windows are empty
    bool AreAllWindowsEmpty();
    // method that calculates all the statistics
    void CalculateStats();

    //PUBLIC VARIABLES AND OBJECTS:
    // variable to keep track of wait time
    int waitTimeVariable;
    //DoublyLinkedList of Students that are used to hold students after they exit the registrar
    DoublyLinkedList<Student*>* pastStudents;
    // queue of student objects called studentQueue
    GenQueue<Student*> *studentQueue;
    // creates new student
    Student* newStudent;
    // new window
    Window* windows;
    //variable that is used to count number of students that visited registrar
    int pastStudentsCount = 0;
    // represents number of windows
    int windowsOpen;

    //variables that are used to hold statistics:
    double meanWait;
    double medianWait;
    int longestWait;
    int numStuWaitOver10;
    double meanWindow;
    int longestWindow;
    int numWinIdleOver5;


private:

    unsigned int arrivalTime;
    int numStudents;
    //creates new window
    Window* newWindow;



};
