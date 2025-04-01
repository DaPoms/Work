/*****************************************************************************/
/*    Author:           Professor Bohdan D. Jacklitsch                       */
/*    Filename:         OrderedLinkedList.cpp                                */
/*    Creation Date:    October 29, 2024                                     */
/*    Last Modified:    November 5, 2024                                     */
/*    Course:           CPSC136-020 - Computer Science II                    */
/*    Purpose:          Implementation of Node class                         */
/*****************************************************************************/
#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node
{
    public:
        /**
            Name:         Constructor
            Description:  Creates the node from the provided values
            Parameters:   string blueprintString (input) -
                            The string to set as the data, defaulting to an
                            empty string
                          Node* nextNode (input) -
                            The node to point to, defaulting to NULL
            Returns:      N/A
        **/
        Node(string blueprintString = "", Node* nextNode = NULL);

        /**
            Name:         Copy Constructor
            Description:  Creates the node from a reference node
            Parameters:   Node referenceNode (input) -
                            The node to copy
            Returns:      N/A
        **/
        Node(const Node& referenceNode);

        /**
            Name:         Destructor
            Description:  Destroys the node
            Parameters:   None
            Returns:      N/A
        **/
        ~Node();

        /**
            Name:         = Operator Overload
            Description:  Overwrites object with a copy of referenceNode
            Parameters:   Node referenceNode (input)
                            The node to copy
            Returns:      A reference to this object
        **/
        Node& operator=(const Node& referenceNode);

        /**
            Name:         < Operator Overload
            Description:  Checks if data of left node is less than data of
                            right Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if this object's data is less than, else false
        **/
        bool operator<(const Node& rightNode);

        /**
            Name:         > Operator Overload
            Description:  Checks if data of left node is more than data of
                            right Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if this object's data is more than, else false
        **/
        bool operator>(const Node& rightNode);

        /**
            Name:         <= Operator Overload
            Description:  Checks if data of left node is less than or equal to
                            data of right Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if this object's data is less than or equal to,
                            else false
        **/
        bool operator<=(const Node& rightNode);

        /**
            Name:         >= Operator Overload
            Description:  Checks if data of left node is more than or equal to
                            data of right Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if this object's data is more than or equal to,
                            else false
        **/
        bool operator>=(const Node& rightNode);

        /**
            Name:         == Operator Overload
            Description:  Checks if data of left node is equal to data of right
                            Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if the two objects' data are equal, else false
        **/
        bool operator==(const Node& rightNode);
        
        /**
            Name:         != Operator Overload
            Description:  Checks if data of left node is unequal to data of
                            right Node
            Parameters:   Node rightNode (input)
                            The node to compare data against
            Returns:      True if the two objects' data are unequal, else false
        **/
        bool operator!=(const Node& rightNode);
        
        /**
            Name:         >> Operator Overload
            Description:  Sets the value of the node from data in a stream
            Parameters:   istream inputStream (input/output)
                            The stream to extract from
                          Node writingNode (output)
                            The Node whose data will be written to
            Returns:      The passed in istream, for chaining
        **/
        friend istream& operator>>(istream& inputStream, Node& writingNode);

        /**
            Name:         << Operator Overload
            Description:  Sends the data of a node to a stream
            Parameters:   ostream outputStream (input/output)
                            The stream to send the data to
                          Node printingNode (input)
                            The Node whose data will be sent to a stream
            Returns:      The passed in ostream, for chaining
        **/
        friend ostream& operator<<(ostream& outputStream, const Node& printingNode);
        
        // Gives OrderedLinkedList unrestricted access to private data
        friend class OrderedLinkedList;
    
    private:
        // The data of the node
        string data;
        
        // The pointer to the next node
        Node* next;
};
#endif