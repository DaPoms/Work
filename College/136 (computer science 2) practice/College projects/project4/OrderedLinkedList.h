/**********************************************************************/
/*    Author:           Daniel Tripoli                                */
/*    Filename:         OrderedLinkedList.h                           */
/*    Creation Date:    11/11/24                                      */
/*    Last Modified:    11/16/24                                      */
/*    Due Date:         11/17/24                                      */
/*    Course:           CPSC136-020 - Computer Science II             */
/*    Professor Name:   Bohdan D. Jacklitsch                          */
/*    Assignment:       Project 4 - linked list                       */
/*    Purpose: Create the OrderedLinkedList class and declare its     */
/*             attributed functions for implementation in the         */
/*             OrderedLinkedList.cpp file                             */          
/**********************************************************************/

#include <iostream>
#include "Node.h"

using namespace std;

class OrderedLinkedList
{
    public:
        
        /**
        Name:         OrderedLinkedList
        Description:  constructs an empty linked list with the head pointing to null          
        Parameters:   None
        Returns:      None
        **/
        OrderedLinkedList();

        /**
        Name:         OrderedLinkedList
        Description:  Constructs a linked list by converting elements of the array into the linked list       
        Parameters:   string blueprintArray[] - an array of strings that holds what the node values will be
                      int numElts - The number of elements we want to add from the array to the linked list
        Returns:      None
        **/

        OrderedLinkedList(string blueprintArray[], int numElts);

        /**
        Name:         OrderedLinkedList
        Description:  Constructs a linked list by copying elements from one linked list to the other      
        Parameters:   OrderedLinkedList& referenceList - the list we want to copy over to the list being constructed
        Returns:      None
        **/

        OrderedLinkedList(const OrderedLinkedList& referenceList);

        /**
        Name:         ~OrderedLinkedList
        Description:  Deletes the elements in a linked list and points its head to NULL      
        Parameters:   OrderedLinkedList& referenceList - the list we want to copy over to the list being constructed
        Returns:      None
        **/
       
        ~OrderedLinkedList();

        /**
        Name:         operator= overload
        Description:  Copies nodes of right operand to the left operand linked list, 
                      making separate nodes with equal values to the right list operand      
        Parameters:   OrderedLinkedList& referenceList - the list we want to copy over to the left list
        Returns:      None
        **/

        OrderedLinkedList& operator=(const OrderedLinkedList& referenceList);

        /**
        Name:         isEmpty
        Description:  tests if a linkedList is empty     
        Parameters:   None
        Returns:      bool - true if linked list is empty, false otherwise
        **/

        bool isEmpty() const;

        /**
        Name:         determineCount
        Description:  finds the number of elements in a linked list    
        Parameters:   None
        Returns:      int - the total elements in the linked list
        **/

        int determineCount() const;

        /**
        Name:         inList
        Description:  tests if any nodes contains the specified string   
        Parameters:   string searchingString - the string that we want to search the nodes for
        Returns:      bool - true if the string is found in a node when traversing the list,
                      false otherwise
        **/

        bool inList(string searchingString) const;

        /**
        Name:         findIndex
        Description:  finds the first node that contains the specified string    
        Parameters:   string searchingString - the string we are looking for 
                      in the nodes of the linked list
        Returns:      int - the index where the string was found in the list, or -1 if 
                      it wasn't found                    
        **/

        int findIndex(string searchingString) const;

        /**
        Name:         atIndex
        Description:  Prints out the value of a node at a given index    
        Parameters:   int searchingIndex - The index of the node we want to print the data of 
        Returns:      string - the string stored in the node at the passed index, an empty string if out of bounds                    
        **/

        string atIndex(int searchingIndex) const;

        /**
            Name:         += Operator Overload (string)
            Description:  Adds a new node, created from the provided string, to
                            the linked list
            Parameters:   string addingString (input) - the string to add to
                                                          the linked list
            Returns:      OrderedLinkedList& - A reference to this object
        **/
       
        OrderedLinkedList& operator+=(const string& addingString);

        /**
        Name:         Operator+= Overload (OrderedLinkedLIst)
        Description:  adds elements of right operand linked list to the left operand linked list,
                      retaining the original nodes from before the operation
        Parameters:   OrderedLinkedList& addingList - the linked list that will copy its nodes to the left operand
        Returns:      OrderedLinkedList& - Returns the left operand linked list to enable chaining                         
        **/

        OrderedLinkedList& operator+=(const OrderedLinkedList& addingList);
        
        /**
        Name:         Operator-= Overload (OrderedLinkedLIst)
        Description:  Removes the first occurence of the passed string if
                      it is found in a node in the left operand linked list
        Parameters:   string& removingString - The string which we use to search for the node we want to delete
        Returns:      OrderedLinkedList& - Returns the left operand linked list to enable chaining                         
        **/

        OrderedLinkedList& operator-=(const string& removingString);

        /**
        Name:         modifyNode
        Description:  Replaces an existing node with a new node of a passed data value
        Parameters:   string oldString - The string we want to find and delete the node of
                      string newData - The data we want to replace the old node with when we put in a new node
        Returns:      OrderedLinkedList& - Returns the left operand linked list to enable chaining                         
        **/

        void modifyNode(string oldString, string newData);

        /**
        Name:         printForwards
        Description:  Prints the list forwards, printing the each node on a separate line
        Parameters:   None
        Returns:      None (void)              
        **/

        void printForwards() const;

        /**
        Name:         printBackwards
        Description:  Holds preconditions and postconditions to setup recursively printing every node's data from a linked list backwards
        Parameters:   None
        Returns:      None (void)                       
        **/

        void printBackwards() const;

        /**
        Name:         operator>> overload
        Description:  Creates a new node from the string read from the istream and
                      adds it to the list in order
        Parameters:   istream& inputStream - The means of userinput
                      OrderedLinkedLIst& writingList - The list that we want to add the node to
        Returns:      istream& - allows chaining of operator>>                    
        **/

        friend istream& operator>>(istream& inputStream, OrderedLinkedList& writingList); //Needs access to private nodes !!!!!

    
    private:
        
        Node* head; // Pointer to the first node in the list

        /**
        Name:         printBackwardsHelper
        Description:  prints out all elements (data of nodes) in a linked list recursively to print backwards
        Parameters:   Node* traverseNodes - The node that we want to print out
        Returns:      None (void)                       
        **/

        void printBackwardsHelper(Node* traverseNodes) const;

        /**
        Name:         copyLinkedList
        Description:  Copies referenceList nodes to the leftList nodes, overwriting the old nodes of the left list
        Parameters:   OrderedLinkedList& leftList - The list we want to copy to
                      OrderedLinkedList& referenceList - The list who's values we use to copy
                      in my implementation of this function using the left list in it's function call
        Returns:      None (void)                       
        **/

        void copyLinkedList(OrderedLinkedList& leftList, const OrderedLinkedList& referenceList);
       
        /**
        Name:         purgeList
        Description:  Deletes nodes in a linked list, preserving the head address though
        Parameters:   OrderedLinkedList& leftList - The list we want to purge, with both uses
                      in my implementation of this function using the left list in it's function call
        Returns:      None (void)                       
        **/
        void purgeList(OrderedLinkedList& leftList);

        /**
        Name:         sortArr
        Description:  Sorts an array of strings from least to greatest alphabetically
        Parameters:   string blueprintArray[] - The array that is to be sorted
                      int numElts - The number of elements we want to sort from the array
        Returns:      None (void)                       
        **/

        void sortArr(std::string blueprintArray[], int numElts); 
        
        
};
