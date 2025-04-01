/**********************************************************************/
/*    Author:           Daniel Tripoli                                */
/*    Filename:         OrderedLinkedList.cpp                         */
/*    Creation Date:    11/11/24                                      */
/*    Last Modified:    11/16/24                                      */
/*    Due Date:         11/17/24                                      */
/*    Course:           CPSC136-020 - Computer Science II             */
/*    Professor Name:   Bohdan D. Jacklitsch                          */
/*    Assignment:       Project 4 - linked list                       */
/*    Purpose: implement functionality of linked list functions       */          
/**********************************************************************/
#include <iostream>
#include "Node.h"
#include "OrderedLinkedList.h"

using namespace std;


void OrderedLinkedList::sortArr(std::string blueprintArray[], int numElts) //Sorts array from least to greatest alphabetically
{
    std::string placeholder; //Used to swap vals in array
    for(int sorted{0}; sorted < numElts; ++sorted)
    {
        for(int traverse{numElts - 1}; traverse > sorted; --traverse)
        {
            if(blueprintArray[traverse] < blueprintArray[traverse - 1]) //Sorts array from least to greatest
            {
                placeholder = blueprintArray[traverse];
                blueprintArray[traverse] = blueprintArray[traverse - 1];
                blueprintArray[traverse - 1] = placeholder;
            }
        }
    }
}

OrderedLinkedList::OrderedLinkedList() //Creates empty linked list with head pointing to null
{
    head = NULL;
}

OrderedLinkedList::OrderedLinkedList(string blueprintArray[], int numElts) //Converts a passed array to a linked list
{
   
    if(numElts != 0) //User must enter numElts = 0 if they copy construct with an empty array, this also makes it more efficient to not run the code if we don't want to insert anything in the list (which is a rare case, but its still cool)
    {
        sortArr(blueprintArray, numElts); //Sorts array so we don't have to worry at all about node organization

        head = new Node{blueprintArray[0]}; //Create start, first node will point to null
        Node* traverseList{head};  //Used to travel through list while keeping head at the start of the list

        for(int i{1}; i < numElts; i++)//Adds 1 new node for every element in the array (excluding the one we added at the start)
        {
            traverseList -> next = new Node{blueprintArray[i]}; //Benefit of default params! Last element in the array will be pointing to null in the list! No need to add code after the for loop for it 
            traverseList = traverseList -> next; //Traverses to the new node we made.
        }
    }

    else //Case of empty array or an array with 0 elements is passed (assuming the programmer actually inputs the right numElts)
        head = NULL;
}

OrderedLinkedList::OrderedLinkedList(const OrderedLinkedList& referenceList) //Creates a separate (deep) copy of the referencesList's nodes to the constructed linked list
{
    copyLinkedList(*this, referenceList); //This was actually kinda tricky to think through
      
    if (!referenceList.head)//Case of if passed list IS empty
        head = NULL;
    
}

void OrderedLinkedList::copyLinkedList(OrderedLinkedList& leftList, const OrderedLinkedList& referenceList) //Helper function for the process of copying elements from the right list (the parameter) to the left list
{
    Node* currReferenceNode = referenceList.head;
    Node* currCopyNode;
 
    if(referenceList.head) //Case of if passed list is not empty
    {
        leftList.head = new Node{referenceList.head -> data}; 
        currCopyNode = leftList.head;
    
        while (currReferenceNode -> next)
        {
            currReferenceNode = currReferenceNode -> next; //Travels to next node in the list we want to copy
            currCopyNode -> next = new Node{currReferenceNode -> data}; //Creates the node next node for the list recieving the copy
            currCopyNode = currCopyNode -> next; //Travels to copied node we just created in the list recieving the copy
        }

    }
}

OrderedLinkedList::~OrderedLinkedList() //Deletes nodes in a list and clears head
{
    purgeList(*this); //Deletes list
    head = NULL;
}

void OrderedLinkedList::purgeList(OrderedLinkedList& leftList) //Deletes nodes in a list, keeping head
{
    Node* prevNode{NULL}; //Why does previous node have to start at NULL
    Node* currNode{leftList.head};

    while(currNode)
    {
        prevNode = currNode; //Do I need new if I am deleting after?
        currNode = currNode -> next;
        delete prevNode;
    }
}

OrderedLinkedList& OrderedLinkedList::operator=(const OrderedLinkedList& referenceList) //Clears the left operand linked list and then creates a deep copy of the referenceList to the left list
{
  
    purgeList(*this);
    copyLinkedList(*this, referenceList);
    return *(this);

}

bool OrderedLinkedList::isEmpty() const //Returns if linked list has no nodes (true) or not (false)
{

if(!head) //Only true when head is pointing to NULL  
 {
    return true;
 }

return false;

}

int OrderedLinkedList::determineCount() const //Returns the number of elements in the linked list
{
    int count{0};
    Node* traverseNode = head;
    while(traverseNode) //Stays true while not null
    {
        ++count;
        traverseNode = traverseNode -> next;
    }

    return count;
}

bool OrderedLinkedList::inList(string searchingString) const //Returns if the passed string is contained within a node of the linked list (true) or not (false)
{
    
    if(head) //Avoids null linked lists from causing a seg fault
    {
         
        Node* traverseNodes = head;
        
        while(traverseNodes)
        {

            if(traverseNodes -> data == searchingString) //I believe this is more efficient that using a node operator, as it'd have to convert the string to a node (I think) to do the comparison
                return true;
          
            traverseNodes = traverseNodes -> next;    
        }
        
    }

    return false;
}

int OrderedLinkedList::findIndex(string searchingString) const //Returns the index of the node that contains the passed string, or -1 if it's not found
{
    int count{0};
    Node* traverseNodes = head;

    while(traverseNodes)
    {
        if(traverseNodes -> data == searchingString) // I could do the fun Node to string implicit comparison again by doing *traverseNodes == searchingString
        {
            return count;
        }

        ++count;
        traverseNodes = traverseNodes -> next;
  
    }

    return -1;
}

string OrderedLinkedList::atIndex(int searchingIndex) const //Returns the value/data of the node at the passed index, or an empty string if it's out of bounds
{
    Node* traverseNode = head;

    if(head && searchingIndex >= 0) //Fix for project 4
    {
        for(int i{0}; (i < searchingIndex) && traverseNode; ++i) //Traverses linked list till the requested index if and only if the index is within the bounds of the list
        {
            traverseNode = traverseNode -> next;
        }

        if(traverseNode) //Makes sure that we do not get a segment fault if we go out of bounds
            return traverseNode -> data;

    }
    return "";
}

// Adds a new node containing the addingString as the data to the list in order
OrderedLinkedList& OrderedLinkedList::operator+=(const string& addingString)
{
    // Construct the node to be added

    Node* tempNode = new Node(addingString);
    Node* currentNode = head;
    Node* previousNode = NULL;
    
    // Case if empty or it belongs at head
    
    if (isEmpty() || *head >= *tempNode ) //Error fixed here, since head and tempNode are pointers, in order to use Node operators, you must dereference! 
    {
        
        tempNode->next = currentNode;
        head = tempNode;
        
        
        return (*this);
    }
    
    // Search
    while (currentNode && *currentNode < *tempNode)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    
    // Case if new node does not belong at head
    previousNode -> next = tempNode;
    tempNode -> next = currentNode;
    return (*this);
}

OrderedLinkedList& OrderedLinkedList::operator+=(const OrderedLinkedList& addingList)  //Copies the passed list nodes to the left linked list but retaining the left list's old nodes, putting the nodes of the passed list in order
//There are definitely improvements to be made on the efficiency scale, but this is the best I could do for now
{   

    Node* traversePassedList = addingList.head; //We do not need to manually delete, its deleted out of scope
    Node* currLeftList{head};
    Node* prevLeftList{NULL};
    Node* tempNode;
    
    if(addingList.head) //For efficiency and preventing seg fault if passed list for += is empty
    { //STILL NEED TO ADD functionality for copying empty
     
        
        if(!head) //Case for copying to a linked list pointing to NULL
        {
            tempNode = new Node{traversePassedList -> data};
            head = tempNode;
            traversePassedList = traversePassedList -> next;
            currLeftList = head;
        }
        
        while(traversePassedList)
        {
            tempNode = new Node{traversePassedList -> data};
         
            if(*tempNode < *head)//Case for belonging to the head
            {
                prevLeftList = currLeftList; //
                currLeftList = tempNode; //
                
                head = tempNode;
                tempNode -> next = prevLeftList;

                traversePassedList = traversePassedList -> next;
                tempNode = new Node{traversePassedList -> data};

            
                
            }
             
            else if(!currLeftList) //Case of adding to the end
            {
                prevLeftList -> next = tempNode;
                traversePassedList = traversePassedList -> next;
                currLeftList = tempNode; //Sets currentNode pointer to new node in the case that a bunch of copied nodes need to be added to the end!
            }

            else if(*tempNode < *currLeftList) //Case for if the Node belongs before an existing node, has to be down here to prevent seg fault of comparing the data of NULL
            {
                prevLeftList -> next = tempNode;
                tempNode -> next = currLeftList;
                traversePassedList = traversePassedList -> next;
                currLeftList = tempNode; //When adding between, we need to set the previous (which will happen at the end of the while loop) as the new node we added or else we don't properly add the next new node if its meant to go after it
            
            }

            

            ///Sets up node insertion position
            prevLeftList = currLeftList; 
            currLeftList = currLeftList -> next;
        }
        
    }
        return (*this);
}

void OrderedLinkedList::modifyNode(string oldString, string newData) //Replaces an existing node in the linked list with a new node
{
    (*this) -= oldString;
    (*this) += newData;
}

OrderedLinkedList& OrderedLinkedList::operator-=(const string& removingString) //Deletes a node in the linked list by finding if a node's data matches the passed string
//It would be inefficient to use findIndex(), as we lose the Node pointer to it unless we make a function that returns it
{
    Node* previousNode = NULL;
    Node* currNode = head;
    bool found{false}; //Used found so that an empty linked list does not get a seg fault

    
        
        while(currNode)
        {
            if(currNode -> data == removingString) // I could do the fun Node to string comparison again by doing *traverseNodes == searchingString
            {
                found = true;
                break; //Stop while loop if string found
            }

            previousNode = currNode;
            currNode = currNode -> next;
    
        }

        if (currNode == head && found)
        {
            head = currNode -> next;
            delete currNode;
        }

        else if (found)
        {
            previousNode -> next = currNode -> next;
            delete currNode;
        }
        
    

    return (*this);
    
}



void OrderedLinkedList::printForwards() const //Prints all the data of all nodes in a linked list in order 
{
    Node* traverseNodes = head;

    while(traverseNodes) //True while not NULL, as traverse is a pointer
    {
        std::cout << traverseNodes -> data << '\n'; 
        traverseNodes = traverseNodes -> next;
    }
}

void OrderedLinkedList::printBackwardsHelper(Node* traverseNodes) const //Does all the recursion processes needed to print the elements of a linked list backwards
{


if (head) //prevents seg fault if head points to null
    traverseNodes = traverseNodes -> next;    

if(traverseNodes)
 {
    printBackwardsHelper(traverseNodes);
    std::cout << traverseNodes -> data << "\n";
 }
   
}
void OrderedLinkedList::printBackwards() const //Prints all the data of all nodes in a linked list in backwards
{
    Node* traverseNodes = head; 
    printBackwardsHelper(traverseNodes);
    
    if(head) //prevents seg fault if head points to null
        std::cout << head -> data;
}

istream& operator>>(istream& inputStream, OrderedLinkedList& writingList) //Takes user input and creates a node in the list with the new node's data being the user's input, putting the node in the spot where it belongs (alphabetical in this case)
{
    std::string inputString{};
    inputStream >> inputString;

    writingList += inputString; //creates new node in order, so it does the work for us!

    return inputStream;
}

//Test indexing issue
//How to get >> operator to work on getline?

//Fix assignment operator to case of list to itself (if address is same for both, then don't do anything)
