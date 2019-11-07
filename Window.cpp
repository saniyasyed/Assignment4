
#include <iostream>
#include "Window.h"

using namespace std;

//constructor for Window object
Window::Window()
{
    timeIdle = 0;
    timeBusy = 0;
    currentStudent = NULL;
    isOpen = true;

}

//method to add a student object s to an open window
void Window::addStudentToWindow(Student* s)
{
    currentStudent = s; // assigining the current student to the parameter Student *s
    isOpen = false; // changing the window's bool variable to false
    timeBusy = s->windowTime; // assigning timeBusy to the student's window time needed
}

// method used to remove student from the window and returns the student 
Student* Window::removeStudent()
{
    isOpen = true; // changing isOpen to true after student is done
    Student* thisStudent = currentStudent; // reassigns thisStudent to currentStudent
    currentStudent = NULL; // changing currentStudent to NULL
    return thisStudent;
}
