#include "Registrar.h"
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

//constructor
Registrar::Registrar()
{
    pastStudents = new DoublyLinkedList<Student*>();
    windowsOpen = 0;
    arrivalTime = 0;
    numStudents = 0;
    studentQueue = new GenQueue<Student*>();
}
// method that reads in a file and fills the studentQueue
void Registrar::FillQueue(string fileName)
{
    // bool variable that is used to check when file has been read through
    bool fileEmpty = false;
    ifstream fileStreamer; // declaring ifstream object used to read file
    fileStreamer.open(fileName); // using fileStreamer to open the fileName
    string line;

    //throws runtime_error if file could not be opened
    if(!fileStreamer)
    {
        throw runtime_error("The file could not be opened.");
    }
    int lineCount = 0; // int variable to represent line count
        //iterating through each line
        while(getline(fileStreamer, line))
        {
            // takes in the number of open windows from the file
            if(lineCount == 0)
            {
                windowsOpen = stoi(line); // assigns the number of windows open as an integer
                lineCount++; //increaments line count
                continue;
            }
            // takes in the current time
            if(lineCount == 1)
            {
                arrivalTime = stoi(line); // assigns the arrival time as an integer
                lineCount++;
                continue;
            }
            // takes in number of students
            if(lineCount == 2)
            {
                numStudents = stoi(line); // assigns the number of students as an integer
                lineCount = 1; // to set lineCount back up to the top to take in a new arrival time

                // iterating through the number of students to check each student's needed window time to create the student object
                for(int i = 0; i < numStudents; ++i)
                {
                    getline(fileStreamer, line);
                    if(fileStreamer.eof()) // if fileStreamer has reached the end of the file
                    {
                        fileEmpty = true; // used to break out of loop
                        break;
                    }
                    // creates new student object with its variables
                    newStudent = new Student(arrivalTime, stoi(line));
                    // pushes new student into the studentQueue
                    studentQueue->insert(newStudent);
                }
                //reassigns numStudents to 0
                numStudents = 0;
                continue;

            }
            // sends the reader back up to the arrival time to look for next student
            if(numStudents == 0)
            {
                lineCount = 1;
            }
            // uses bool variable to check if file has been completely read
            if(fileEmpty == true)
            {
                break;
            }
        }
}

// method to fill all the windows with the correct number of window objects
void Registrar::FillWindows()
{
    windows = new Window[windowsOpen];
}

// method to populate the windows and goes through every time iteration as one clock tick
void Registrar::PopulateWindows(int currentTime)
{
    // iterating through the number of windows that are open
    for(int i = 0; i < windowsOpen; ++i)
    {
        // checking if the current window is open
        if(windows[i].isOpen == true)
        {
            // making sure that we are not trying to remove a student from an empty queue
            if(!studentQueue->isEmpty())
            {
                // creates new student with the front student of the studentQueue
                Student *stu = studentQueue->peek();
                // checking if the student's timeArrived variable is less than or equal to the current registrar's time
                if(stu->timeArrived <= currentTime)
                {
                    // removing student from the studentQueue
                    Student *thisStudent = studentQueue->remove();
                    // calling setWaitTime method to assign the student's wait time by subtracting the student's timeArrived variable from waitTimeVariable
                    thisStudent->setWaitTime(waitTimeVariable - thisStudent->timeArrived);
                    // calls the addStudentToWindow to bring the current student to the open window
                    windows[i].addStudentToWindow(thisStudent);
                }
                else
                {
                    break;
                }
            }
        }
    }
}

// method used to remove students from the windows and push them to the pastStudentsCount DoublyLinkedList
void Registrar::DepopulateWindows()
{
    //iterating through the number of open windows
    for(int i = 0; i < windowsOpen; ++i)
    {
        // if they are not open
        if(windows[i].isOpen == false)
        {
            // and if they are not busy, meaning that the student is done
            if(windows[i].timeBusy == 0)
            {
                // remove student from the window and push them to the pastStudents list
                pastStudents->insertBack(windows[i].removeStudent());
                // incrementing the pastStudentsCount to keep track of the total number of students
                pastStudentsCount++;
            }
        }
    }
}

// method to increment the time idle for all the windows
void Registrar::IncrementTimeIdleForAll()
{
    // iterating through each open window
    for(int i = 0; i < windowsOpen; ++i)
    {
        // if the window is idle
        if(windows[i].isOpen == true)
        {
            //increment window's timeIdle variable
            windows[i].timeIdle += 1;
        }
    }
}

// method that checks if the windows are empty and returns true if they are
bool Registrar::AreAllWindowsEmpty()
{
    // bool variable to check
    bool isItEmpty = true;
    // iterating through the windows
    for(int i = 0; i < windowsOpen; ++i)
    {
        // if a window is not open, then set the variable to false
        if(windows[i].isOpen == false)
        {
            isItEmpty = false;
        }
    }

    return isItEmpty;
}


// method that calculates the statistics of the registrar simulation
void Registrar::CalculateStats()
{
  // creating a new array of integers with a size of the the total number of students that visited the registrar
  int waitTimesArr[pastStudentsCount];
  //iterating through the pastStudents list
  for(int i = 0; i < pastStudentsCount; ++i)
  {
    //removing the current student from the pastStudents list and pushing each student's wait time into the waitTimesArr
    waitTimesArr[i] = pastStudents->removeFront()->waitTime;
  }
  // sorting the waitTimesArr
  sort(waitTimesArr, waitTimesArr + pastStudentsCount);
  // CALCULATING WAIT TIME MEAN
  // variable used to calculate the sum of all the wait times
  int waitTimeSum = 0;
  // iterating through the waitTimesArr
  for(int i = 0; i < pastStudentsCount; ++i)
   {
     // adding each wait time to the the waitTimeSum
     waitTimeSum += waitTimesArr[i];
   }
   //dividing waitTimeSum by the number of students to find mean
   meanWait = waitTimeSum / pastStudentsCount;

   //CALCULATING MEDIAN
   // creating variable to represent the middle index to find median
   int middle = pastStudentsCount / 2.0;
   // if the number of students is even, then the median is the average of the two middle wait times in the waitTimesArr
   if(pastStudentsCount % 2 == 0)
   {
       medianWait = (waitTimesArr[middle] + waitTimesArr[middle + 1]) / 2.0;
   }
   else // if the number of students is odd, then the median is the middle value of the waitTimesArr
   {
       medianWait = waitTimesArr[middle] / 1.0 ;
   }

   // FINDING LONGEST WAIT TIME
   // setting longestWait to the last value of the waitTimesArr
   longestWait = waitTimesArr[pastStudentsCount - 1];

   // FINDING THE NUMBER OF STUDENTS THAT HAD A WAIT TIME OF OVER 10 MINUTES
   // iterating through the waitTimesArr
   for(int i = 0; i < pastStudentsCount; ++i)
   {
      // if the wait time at i is greater than 10, increment numStuWaitOver10
       if(waitTimesArr[i] > 10)
       {
           numStuWaitOver10++;
       }
   }

   // creating new array of integers to represent all the window's timeIdle variable
   int windowIdleTimesArr[windowsOpen];
   // iterating through the number of windows
   for(int i = 0; i < windowsOpen; ++i)
   {
      // assigning each index of the array to the window's timeIdle
      windowIdleTimesArr[i] = windows[i].timeIdle;
   }
   // sorting the windowIdleTimesArr
   sort(windowIdleTimesArr, windowIdleTimesArr + windowsOpen);
   // CALCULATING THE WINDOW IDLE TIME MEAN
   int windowSum = 0;
   //iterating through the list to add each idle time to the total sum
   for(int i = 0; i < windowsOpen; ++i)
   {
       windowSum += windowIdleTimesArr[i];
   }
   //dividing the sum by the number of windows to find mean
   meanWindow = windowSum / windowsOpen;

   //FINDING THE LONGEST WINDOW TIME
   // assigning longestWindow to the last value of the windowIdleTimesArr
   longestWindow = windowIdleTimesArr[windowsOpen - 1];

   // FINDING THE NUMBER OF WINDOWS WITH AN IDLE TIME OF OVER 5 MINUTES
   // iterating through the windowIdleTimesArr
   for(int i = 0; i < windowsOpen; ++i)
   {
        // if the window idle time is greater than 5, increment numWinIdleOver5
       if(windowIdleTimesArr[i] > 5)
       {
           numWinIdleOver5++;
       }
   }

   // printing out all the calculated statistics
   cout << "The mean student wait time: " << meanWait << endl;
   cout << "The median student wait time: " << medianWait << endl;
   cout << "The longest student wait time: " << longestWait << endl;
   cout << "The number of students waiting over 10 minutes: " << numStuWaitOver10 << endl;
   cout << "The mean window idle time: " << meanWindow << endl;
   cout << "The longest window idle time: " << longestWindow << endl;
   cout << "Number of windows idle for over 5 minutes: " << numWinIdleOver5 << endl;
}
