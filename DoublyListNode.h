#include<iostream>

using namespace std;
template <class T>
class DoublyListNode
{
public:
    T data;
    DoublyListNode<T> *next;
    DoublyListNode<T> *prev;

    //constructor
    DoublyListNode()
    {
        data = NULL;
        next = NULL;
        prev = NULL;
    }
    //overloaded constructor
    DoublyListNode(T d)
    {
        data = d;
        next = NULL; //nullpointer
        prev = NULL;
    }
    //destructor
    ~DoublyListNode()
    {
        if(next == NULL)
            delete next;
            prev = NULL;
    }

};
