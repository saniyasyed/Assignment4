#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "GenQueue.h"

using namespace std;

class Student
{
public:
    Student(); // constructor
    Student(int tA, int winT); //overloaded constructor

    void setWaitTime(int wait); //method to set the student's wait time

    //public member variables 
    int timeArrived;
    int waitTime;
    int windowTime;

};
#endif
