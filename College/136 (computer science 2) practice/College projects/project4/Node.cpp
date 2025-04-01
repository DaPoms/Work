/**********************************************************************/
/*    Author:           Professor Bohdan D. Jacklitsch                */
/*    Filename:         OrderedLinkedList.cpp                         */
/*    Creation Date:    October 29, 2024                              */
/*    Last Modified:    November 4, 2024                              */
/*    Course:           CPSC136-020 - Computer Science II             */
/*    Purpose:          Header of Node class                          */
/**********************************************************************/

#include <iostream>
#include "Node.h"

using namespace std;

// Constructor, defaulted to an empty string and NULL
Node::Node(string blueprintString, Node* nextNode) //Reminder to self: You can only put default params in the header file forward declare
{
    data = blueprintString;
    next = nextNode;
}

// Copy Constructor
Node::Node(const Node& referenceNode)
{
    data = referenceNode.data;
    next = referenceNode.next;
}

// Destructor
Node::~Node()
{ }

// Assignment Operator Overload
Node& Node::operator=(const Node& referenceNode)
{
    data = referenceNode.data;
    next = referenceNode.next;
    
    return (*this);
}

// Less than Operator Overload
bool Node::operator<(const Node& rightNode)
{
    return ((*this).data < rightNode.data);
}

// Greater than Operator Overload
bool Node::operator>(const Node& rightNode)
{
    return ((*this).data > rightNode.data);
}

// Less than or equals to Operator Overload
bool Node::operator<=(const Node& rightNode)
{
    return ((*this).data <= rightNode.data);
}

// Greater than or equals to Operator Overload
bool Node::operator>=(const Node& rightNode)
{
    return ((*this).data >= rightNode.data);
}

// Equivalancy Operator Overload
bool Node::operator==(const Node& rightNode)
{
    return ((*this).data == rightNode.data);
}

// Inequivalancy Operator Overload
bool Node::operator!=(const Node& rightNode)
{
    return ((*this).data != rightNode.data);
}

// Stream Extraction Operator Overload
istream& operator>>(istream& inputStream, Node& writingNode)
{
    inputStream >> writingNode.data;
    return inputStream;
}

// Stream Insertion Operator Overload
ostream& operator<<(ostream& outputStream, const Node& printingNode)
{
    outputStream << printingNode.data;
    return outputStream;
}
