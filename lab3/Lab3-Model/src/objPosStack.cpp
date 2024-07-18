#include "objPosStack.h"
#include "objPosDLinkedList.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

// Available Data Members from objPosStack.h (Must Review)
//
//      objPosList* myList
//      
//  This is the polymorphic list pointer to the underlying List data structure to
//   support all Stack functionalities
//
//  You should use objPosDLinkedList as your main design param


objPosStack::objPosStack()
{
    // Constructor
    //   Instantiate myList as objPosDLinkedList.  You may use objPosArrayList for testing purpose only.
    myList = new objPosDLinkedList();
}


objPosStack::~objPosStack()
{
    // Destructor
    //  Just delete myList (and all otherheap members, if any)
    delete myList;
}


// private helper function
void objPosStack::generateObjects(int count)
{
    // Generate and pushes individual objPos isntances with randomly generated Prefix, Number, and Symbol.
    // The total number of generated instances is capped by input variable **count**.
    
    // 1. Generate Prefix A-Z and a-z.  Alphabetic characters only.
    // 2. Generate Number [0, 99]
    // 3. Leave Symbol as *
    // Push every randomly generately objPos into the Stack.
    int randPF = 0;
    int randNum = 0;

    for (int i = 1; i <= count; i++) {
        randPF = rand() % 26 + 'A';
        if (rand() % 2) randPF += 32;
        randNum = rand() % 100;
        push(objPos(0, 0, randPF, randNum, '*'));
    }
}


// private helper function
int objPosStack::sortByTenScoreBS()
{
    // Use BUBBLE SORT to sort all the objPos instances in the Stack in ascending order using teh doigit of 10
    //  of the **number** field of objPos.

    // You can use the relevant insertion and removal methods from the objPosDLinkedList interface
    //  to complete the sorting operations.

    // Recommendation - use set() and get() - Think about how
    int n = myList->getSize(); 
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            objPos obj1 = myList->get(j);
            objPos obj2 = myList->get(j + 1);


            int first = (obj1.getNum() / 10) % 10;
            int second = (obj2.getNum() / 10) % 10;

            if (first > second) {
                objPos temp = obj1;
                myList->set(obj2, j);
                myList->set(temp, j+1);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return 0; 
    
}


void objPosStack::populateRandomElements(int size)
{
    // This function generates the number of randomly generated objPos instances with uninitialized
    //  x-y coordinate on the Stack, then sort them in ascending order using the digit of 10
    //  of the **number** field in objPos instances.

    // Implementation done.  You'd have to implement the following two private helper functions above.
    srand(time(NULL));
    generateObjects(size);
    sortByTenScoreBS();
}



void objPosStack::push(const objPos &thisPos) const
{
    // Push thisPos on to the Stack.
    //  Think about which objPosDLinkedList method can realize this operation.
    myList->insertHead(thisPos);
}

objPos objPosStack::pop()
{
    // Pop the top element of the Stack.
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.
    if (myList->isEmpty()){
        return objPos(-99, 0, 0, 0, 0);
    }    
    else {
        return myList->removeHead();
    }
}

objPos objPosStack::top()
{
    // Return the top element of the Stack without removing it
    //  If the Stack is empty, return objPos(-99, 0, 0, 0, 0)
    //  Think about which objPosDLinkedList methods can realize this operation.
    if (myList->isEmpty()){
        return objPos(-99, 0, 0, 0, 0);
    }    
    else {
        return myList->getHead();
    }
}

int objPosStack::size()
{
    // Return the size of the Stack 
    //  Think about which objPosDLinkedList method can realize this operation.
    return myList->getSize();
}

void objPosStack::printMe()
{
    // NOT GRADED
    //  Print the contents of the Stack
    //  Think about which objPosDLinkedList method can partially realize this operation.
    myList->printList();
    // IMPORTANT: USE THIS METHOD FOR DEBUGGING!!!
}