#include <iostream>
#include "Student.h"

using namespace std;

//constructor
Student::Student()
{
    timeArrived = 0;
    windowTime = 0;
    waitTime = 0;
}

//overloaded constructor
Student::Student(int tA, int winT)
{
    timeArrived = tA;
    windowTime = winT;
    waitTime = 0;
}

// method that sets the wait time for each student
void Student::setWaitTime(int wait)
{
    waitTime = wait;
}
