#include "DoublyListNode.h"
using namespace std;
template <class T>
class DoublyLinkedList
{
public:
    //declaring public variables
    DoublyListNode<T> *front;
    DoublyListNode<T> *back;
    unsigned int size;

    //constructor for DoublyLinkedList
    DoublyLinkedList()
    {
        front = NULL; //nullptr
        back = NULL;
        size = 0;
    }
    //destructor for DoublyLinkedList
    ~DoublyLinkedList()
    {
    }

    // method to insert a new node at the front of the DoublyLinkedList
    void insertFront(T d)
    {
        DoublyListNode<T> *node = new DoublyListNode<T>(d);
        if(isEmpty())
        {
            back = node;
        }
        else
        {
            front -> prev = node;
            node -> next = front;
        }
        front = node;
        size++;
    }

    // method to insert a new node at the back of the DoublyLinkedList
    void insertBack(T d)
    {
        // creating new node to insert into DoublyLinkedList
        DoublyListNode<T> *node = new DoublyListNode<T>(d);
        //checking if list is empty
        if(isEmpty())
        {
            front = node;
            back = node;
        }
        else
        {
            back-> next = node;
            node-> prev = back;
        }

        back = node;
        size++;
    }

    // method to remove the front node of the DoublyLinkedList and return the node
    T removeFront()
    {
        // creating new node ft, and setting to front
        DoublyListNode<T> *ft = front;
        //checking if list is empty
        if(front->next == NULL)
        {
            back = NULL;
        }
        else
        {
            front->next->prev = NULL;
        }
        //updating front node
        front = front->next;
        //putting in ft data into temp
        T temp = ft->data;
        //set the pointer for ft to NULL
        ft->next = NULL;
        //decrementing the size
        size--;
        //deleting original node
        delete ft;
        //returning data
        return temp;
    }

    //method to delete a node from the DoublyLinkedList at a specific position
    T deletePos(T pos)
    {
        int idx = 0;
        //creating pointer nodes current and previous and assigning them to front
        DoublyListNode<T> *curr = front;
        DoublyListNode<T> *prev = front;
        while (idx != pos)
        {
            prev = curr; //make sure previous stays back 1
            curr = curr->next;
            idx++;
        }
        prev->next = curr-> next;
        curr->next = NULL;
        T temp = curr->data;
        delete curr;
        size--;
        return temp;
    }

    // method that finds and returns data
    T find(T d)
    {
        int idx = 0;
        DoublyListNode<T> *curr = front;

        while(curr != NULL)
        {
            if(curr -> data == d)
            {
                break;
            }
            idx++;
            curr = curr -> next;
        }

        if(curr == NULL)
        {
            idx = -1;
        }
        return idx;
    }

    // method that returns true if the list is empty, false if not
    bool isEmpty()
    {
        if(size == 0)
            return true;
        else
            return false;
    }

    // method that prints out the data at every index of the list
    void printList()
    {
        DoublyListNode<T> *curr = front;
        while (*curr != NULL)
        {
            cout << curr->data << endl;
            curr = curr->next;

        }
    }

    // method that returns the size of the list
    unsigned int getSize()
    {
        return size;
    }

    // method that finds the value at a specific index
    T getIndex(int idx)
    {
        DoublyListNode<T> *curr = front;
        for(int i = 0; i < idx; ++i)
        {
            curr = curr -> next;
        }
        return curr->data;
    }

};
