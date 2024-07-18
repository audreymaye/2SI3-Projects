#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    listHead = new DNode();
    listTail = new DNode();
    listHead->next = listTail;
    listTail->prev = listHead;
    persistHead = listHead;
    listSize = 0;

}

objPosDLinkedList::~objPosDLinkedList()
{
    DNode* targetNode = listHead;
    while (targetNode != nullptr)
    {
        DNode* readerHead = targetNode->next;
        delete targetNode;
        targetNode = readerHead;
    }
    listHead = nullptr;
    listTail = nullptr;
}

int objPosDLinkedList::getSize()
{
    return listSize;
}

bool objPosDLinkedList::isEmpty()
{
   return listSize == 0;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* newElement = new DNode();
    newElement->data = thisPos;

    newElement->next = listHead->next;
    newElement->prev = listHead;
    listHead->next = newElement;
    newElement->next->prev = newElement;

    listSize++;
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
    DNode* newElement = new DNode();
    newElement->data = thisPos;

    newElement->next = listTail;
    newElement->prev = listTail->prev;
    listTail->prev = newElement;
    newElement->prev->next = newElement;
    
    

    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
   if (index <= 0)
   {
        insertHead(thisPos);
   }
   else if (index >= listSize -1)
   {
        insertTail(thisPos);
   }
   else
   {
        DNode* newElement = new DNode();
        newElement->data = thisPos;

        DNode* targetNode = listHead;
        for (int i = 0; i < index; i++)
        {
            targetNode = targetNode->next;
        }

        newElement->next = targetNode->next;
        newElement->prev = targetNode;
        targetNode->next->prev = newElement;
        targetNode->next = newElement;

        listSize++;
   }
   
}

objPos objPosDLinkedList::getHead() const
{
    return listHead->next->data;
}

objPos objPosDLinkedList::getTail() const
{
    return listTail->prev->data;
}

objPos objPosDLinkedList::get(int index) const
{
    if (index <= 0)
    {
        return getHead();
    }
    else if (index >= listSize -1)
    {
        return getTail();
    }
    else
    {
         DNode* targetNode = listHead->next;
        for (int i = 0; i < index; i++)
        {
            targetNode = targetNode->next;
        }
        return targetNode->data;
    }
}

objPos objPosDLinkedList::getNext()
{
    if (persistHead->next == listTail)
    {
        persistHead = listHead;
        return objPos(-99, 0, 0, 0, 0);
    }
    persistHead = persistHead->next;
    return persistHead->data;
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if (index < 0)
    {
        index = 0;
    }
    else if (index >= listSize)
    {
        index = listSize -1;
    }
    DNode* targetNode = listHead->next;
    for (int i = 0; i < index; i++)
    {
        targetNode = targetNode->next;
    }
    targetNode->data = thisPos;
}


objPos objPosDLinkedList::removeHead()
{
    if (isEmpty())
    {
        return objPos(-99, 0, 0, 0, 0);
    }
    DNode* firstNode = listHead->next;
    objPos data = firstNode->data;
    listHead->next = firstNode->next;
    firstNode->next->prev = listHead;
    delete firstNode;

    listSize--;
    return data;
}

objPos objPosDLinkedList::removeTail()
{
    if (isEmpty())
    {
        return objPos(-99, 0, 0, 0, 0);
    }
    DNode* lastNode = listTail->prev;
    objPos data = lastNode->data;
    lastNode->prev->next = listTail;
    listTail->prev = lastNode->prev;
    delete lastNode;

    listSize--;
    return data;
}

objPos objPosDLinkedList::remove(int index)
{
    if (isEmpty())
    {
        return objPos(-99, 0, 0, 0, 0);
    }

    if (index <= 0)
    {
        return removeHead();
    }
    else if (index >= listSize -1)
    {
        return removeTail();
    }
    else
    {
        DNode* targetNode = listHead->next;
        for (int i = 0; i < index; i++ )
        {
            targetNode = targetNode->next;
        }
        objPos data = targetNode->data;
        targetNode->prev->next = targetNode->next;
        targetNode->next->prev = targetNode->prev;
        delete targetNode;

        listSize--;
        return data;
    }

}


void objPosDLinkedList::printList() const
{
    cout << "Head: " << listHead << endl;
    cout << "Dummy Header (Address: " << listHead << ")" << endl;
    cout << "Data: " << listHead->data.getX() << ", " << listHead->data.getY() << ", " 
                  << listHead->data.getNum() << ", " << listHead->data.getPF() << ", " 
                  << listHead->data.getSym() << endl;
    cout << "Next: " << listHead->next << endl;
    cout << "Prev: " << listHead->prev << endl;

    DNode* targetNode = listHead->next;
    int indexNode = 1;

    while (targetNode != listTail) 
    {
        cout << "Element " << indexNode << " (Address: " << targetNode << ")" << endl;
        cout << "Data: " << targetNode->data.getX() << ", " << targetNode->data.getY() << ", " 
                    << targetNode->data.getNum() << ", " << targetNode->data.getPF() << ", " 
                    << targetNode->data.getSym() << endl;
        cout << "Next: " << targetNode->next << endl;
        cout << "Prev: " << targetNode->prev << endl;

        targetNode = targetNode->next;
        indexNode++;
    }

    cout << "Tail: " << listTail << endl;
    cout << "Dummy Header (Address: " << listTail << ")" << endl;
    cout << "Data: " << listTail->data.getX() << ", " << listTail->data.getY() << ", " 
                  << listTail->data.getNum() << ", " << listTail->data.getPF() << ", " 
                  << listTail->data.getSym() << endl;
    cout << "Next: " << listTail->next << endl;
    cout << "Prev: " << listTail->prev << endl;
}


