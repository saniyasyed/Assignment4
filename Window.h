#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include "Student.h"

using namespace std;

class Window
{
public:
  Window(); // constructor
  // public member variables
  int timeBusy;
  bool isOpen;
  int timeIdle;
  // method to add student to a window
  void addStudentToWindow(Student* s);
  // method to remove student from a window
  Student* removeStudent();
  // pointer object representing the current student 
  Student* currentStudent;
};
#endif
