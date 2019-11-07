#ifndef GENQUEUE_H
#define GENQUEUE_H
#include "DoublyLinkedList.h"
#include <iostream>
template <class T>


class GenQueue
{
public:
    //constructor
    GenQueue()
    {
        myQueue = new DoublyLinkedList<T>();

    }
    //destructor
    ~GenQueue()
    {
    }

    // method that inserts data into the back of the queue
    void insert(T data)
    {
        myQueue->insertBack(data);
    }

    // method that removes the value from the front of the queue and returns the value
    T remove()
    {
        T c = myQueue->removeFront();
        return c;
    }

    // method that returns the front value of the queue
    T peek()
    {
        return myQueue-> front->data;
    }

    // method that returns true if the queue is empty
    bool isEmpty()
    {
        return (myQueue->getSize() == 0);
    }

    //method that returns the size of the queue
    int getSize()
    {
        return myQueue->getSize();
    }

private:
  
    // DoublyLinkedList that is used to create myQueue
    DoublyLinkedList<T> *myQueue;

};

#endif
