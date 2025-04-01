/**********************************************************************/
/*    Author:           Daniel Tripoli                                */
/*    Filename:         project4.cpp                                  */
/*    Creation Date:    11/11/24                                      */
/*    Last Modified:    11/16/24                                      */
/*    Due Date:         11/17/24                                      */
/*    Course:           CPSC136-020 - Computer Science II             */
/*    Professor Name:   Bohdan D. Jacklitsch                          */
/*    Assignment:       Project 4 - linked list                       */
/*    Purpose: test linked list functionality                         */          
/**********************************************************************/

#include <iostream>
#include "OrderedLinkedList.h"

using namespace std;


/**
    Name:         addingNodeTest
    Description:  An incredibly simple function, used to (non-rigerously) test
                    the constructor, += (string), and printing functionalities
                    of OrderedLinkedList
    Parameters:   None
    Returns:      void
**/
void addingNodeTest();

/**
    Name:         arrayConversionTest
    Description:  Tests the constructor for OrderedLinkedList that takes an array and numElts as its parameters         
    Parameters:   None
    Returns:      void
**/

void arrayConversionTest();

/**
    Name:         isEmptyTest
    Description:  Tests the isEmpty function from the OrderedLinkedList class           
    Parameters:   None
    Returns:      void
**/

void isEmptyTest();

/**
    Name:         determineCountTest
    Description:  Tests the determineCount function from the OrderedLinkedList class           
    Parameters:   None
    Returns:      void
**/

void determineCountTest();

/**
    Name:         atIndexTest
    Description:  Tests the atIndex function from the OrderedLinkedList class       
    Parameters:   None
    Returns:      void
**/

void atIndexTest();

/**
    Name:         printBackwardsTest
    Description:  Tests the printBackwards function from the OrderedLinkedList class,
                  including edge cases     
    Parameters:   None
    Returns:      void
**/

void printBackwardsTest();

/**
    Name:         inListTest
    Description:  Tests the inList function from the OrderedLinkedList class          
    Parameters:   None
    Returns:      void
**/

void inListTest();

/**
    Name:         findIndexTest
    Description:  Tests the findIndex function from the OrderedLinkedList class           
    Parameters:   None
    Returns:      void
**/

void findIndexTest();

/**
    Name:         copyConstructorTest
    Description:  Tests the copy constructor from the OrderedLinkedList class 
                  that has a linked list as its parameter, and tests normal and edge
                  cases          
    Parameters:   None
    Returns:      void
**/


void copyConstructorTest();

/**
    Name:         minusEqualsTest
    Description:  Tests the operator-= from the OrderedLinkedList class            
    Parameters:   None
    Returns:      void
**/

void minusEqualsTest();

/**
    Name:         assignmentOperatorTest
    Description:  Tests the operator>> from the OrderedLinkedList class            
    Parameters:   None
    Returns:      void
**/

void assignmentOperatorTest();

/**
    Name:         plusEqualsListTest
    Description:  Tests the operator+= (with OrderedLinkedList parameter) from the OrderedLinkedList class              
    Parameters:   None
    Returns:      void
**/

void plusEqualsListTest();

/**
    Name:         equalsTest
    Description:  Tests the operator= from the OrderedLinkedList class and checks
                  that the left operand list is separate from the right operand list              
    Parameters:   None
    Returns:      void
**/

void equalsTest();


/**
    Name:         plusEqualsListTest
    Description:  Tests the modifyNode function from the OrderedLinkedList class              
    Parameters:   None
    Returns:      void
**/

void modifyNodeTest();

int main() //Made is so you can test each factor one at a time by uncommenting
{
    addingNodeTest(); 
    arrayConversionTest(); 
    isEmptyTest();
    determineCountTest();
    atIndexTest();
    printBackwardsTest();
    inListTest();
    findIndexTest();
    copyConstructorTest();
    minusEqualsTest();
    assignmentOperatorTest();
    plusEqualsListTest();
    equalsTest();
    modifyNodeTest();
    return 0;
}

// A simple, non-rigerous testing function
void addingNodeTest() //Supposedly bugged?
{
    OrderedLinkedList testList;
    

    testList += "bapples"; 

    testList += "can"; 

    testList += "and";

    
    testList.printForwards();
}

void arrayConversionTest()
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; //In order for this to work, we expect user input to be of the same capitalization standard
    OrderedLinkedList testList{arr, 6};

    std::cout << "Test if hard coded filled array is successfuly converted to  linked list:\n";
    testList.printForwards();

    std::string arr2[1]; 
    OrderedLinkedList testList2{arr2, 1}; 

    std::cout << "\nTest if hard coded array of 0 elements is successfuly converted to linked list:\n";
    testList2.printForwards();

    std::string arr3[1] = {"loss"}; 
    OrderedLinkedList testList3{arr3, 1};

    std::cout << "\nTest if hard coded array of 1 elements is successfuly converted to linked list:\n";
    testList3.printForwards();
}

void isEmptyTest()
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; //In order for this to work, we expect user input to be of the same capitalization standard
    OrderedLinkedList filledList{arr, 6}; //Does this need to work with an empty array????
    OrderedLinkedList emptyList{};
    
    std::string emptyArr[5]; //Do we need to make a case for when the user has an empty array as input
    OrderedLinkedList uninitializedList{emptyArr, 5};

    std::cout << "Test if hard coded array is successfuly detected as not being empty (should be false):\n" << std::boolalpha << filledList.isEmpty();
    

    std::cout << "\nTest if hard coded array is successfuly detected as being empty (should be true):\n" << emptyList.isEmpty();

    
    std::cout << "\nTesting edge case of array being uninitialized:\n" << uninitializedList.isEmpty(); //results in false as it fills the linked list with garbage values converted to strings

}

void determineCountTest()
{
     std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; 
     OrderedLinkedList filledList{arr, 6};

     OrderedLinkedList emptyList{};

     std::cout << "Count of linked list with 6 elements: " << filledList.determineCount();
     std::cout << "\nCount of linked list with 0 elements: " << emptyList.determineCount();
}

void atIndexTest()
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    OrderedLinkedList emptyList{};

    filledList.printForwards();

    std::string arr2[1] = {"zeta"}; 
    OrderedLinkedList filledList2{arr2, 1};
    std::cout << "\nValue at 1st element in list of only 'zeta' (index 0): " << filledList2.atIndex(0);


    std::cout << "\n\nValue at 3rd element in list (index 2): " << filledList.atIndex(2);
    std::cout << "\nValue at an out of bounds point: " << filledList.atIndex(100);
    std::cout << "\nValue at 3rd element in list (index 2, but list is empty): " << emptyList.atIndex(2);
}

void printBackwardsTest()
{
    std::string arr[6] = { "ban", "ab", "zeta", "test", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    std::cout << "Ordered linked list of 6 elements printed backwards (greatest to least alphabetical order): \n";
    filledList.printBackwards();
    std::cout << "\n\n";


    std::string oneArr[1] = {"zeta"}; 
    OrderedLinkedList oneEleList{oneArr, 1};

    std::cout << "Ordered linked list of 1 element printed backwards (greatest to least alphabetical order): \n";
    oneEleList.printBackwards();
    std::cout << "\n\n";


    OrderedLinkedList nullList{};
    std::cout << "Ordered linked list of 0 elements printed backwards (greatest to least alphabetical order): \n";
    nullList.printBackwards();
    std::cout << "\n\n";



}

void inListTest()
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    std::cout << "Whether or not 'test' is in the list (should be true): \n" << filledList.inList("test");
     std::cout << "\nWhether or not 'apple' is in the list (should be false): \n" << filledList.inList("apple");
    std::cout << "\n\n";


    std::string oneArr[1] = {"zeta"}; 
    OrderedLinkedList oneEleList{oneArr, 1};

    std::cout << "Whether or not 'zeta' is in the list (should be true): \n" << oneEleList.inList("zeta");
    std::cout << "\nWhether or not 'cookie' is in the list (should be false): \n" << oneEleList.inList("cookie");
   
    std::cout << "\n\n";


    OrderedLinkedList nullList{};
    std::cout << "\nWhether or not 'a' is in the list (should be false): \n" << nullList.inList("a");
    std::cout << "\n\n";

}

void findIndexTest()
{
    std::string arr[6] = {"test", "zeta", "ban", "ab", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    filledList.printForwards();
    std::cout << "\nIndex of 'test' in the list (should be 4): \n" << filledList.findIndex("test");
    std::cout << "\nIndex of 'test' in the list (should be 0): \n" << filledList.findIndex("ab");
    std::cout << "\nIndex of 'zeta' in the list (should be 5): \n" << filledList.findIndex("zeta");
    std::cout << "\n==========================\n";


    std::string oneArr[1] = {"zeta"}; 
    OrderedLinkedList oneEleList{oneArr, 1};

    oneEleList.printForwards();
    std::cout << "\nIndex of 'zeta' in the list (should be 0): \n" << oneEleList.findIndex("zeta");
    std::cout << "\nIndex of 'cookie' in the list (should be -1): \n" << oneEleList.findIndex("cookie");
   
    std::cout << "\n==========================\n";


    OrderedLinkedList nullList{};
    std::cout << "\nWhether or not 'a' is in an empty list (should be -1): \n" << nullList.findIndex("a");
    std::cout << "\n\n";
}

void copyConstructorTest()
{
    std::string arr[6] = {"test", "zeta", "ban", "ab", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};
    OrderedLinkedList copyList{filledList};
    std::cout << "Copying 6 element linked list:\n";
    copyList.printForwards();
    
    std::cout << "\n\nTest that the copied list is separate from the original list:\n";
    copyList.modifyNode("ban", "ImSeparate!");
    copyList.printForwards();
    std::cout << "\n";
    filledList.printForwards();

    std::string arr2[1]; 
    //std::string arr2[0]; //This is weird, it lets me create arrays of size 0 in UNIX but not vsCode (from what I saw you should not be able to create size 0 arrays)
    OrderedLinkedList twoEle{arr2, 1};
    OrderedLinkedList copiedList2{twoEle};
    std::cout << "\n\n";
    std::cout << "Copying 0 element linked list:\n";
    copiedList2.printForwards();
    
}

void minusEqualsTest()
{
    std::string arr[6] = {"test", "zeta", "ban", "ab", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    OrderedLinkedList emptyList{};

    std::cout << "testing deleting all items in linked list of 6 elements with -= operator:\n";

    filledList -= "ab"; 
    filledList.printForwards();
    std::cout << "\n\n";

    filledList -= "test";
    filledList.printForwards();
    std::cout << "\n\n";

    filledList -= "lab";
    filledList.printForwards();
    std::cout << "\n\n";

    filledList -= "era";
    filledList.printForwards();
    std::cout << "\n\n";

    filledList -= "ban";
    filledList.printForwards();
    std::cout << "\n\n";

    filledList -= "zeta";
    filledList.printForwards();
    std::cout << "\n\n";

    std::cout << "=================================\nTest of deleting once linked list is empty (no error = good!):\n";

    filledList -= "zeta";
    filledList.printForwards();
    std::cout << "\n\n";

    std::cout << "=================================\nTest of deleting from a null linked list (should do nothing):\n";
    emptyList -= "blob";
    emptyList.printForwards();
    
}

void assignmentOperatorTest()
{
    std::string arr[6] = {"test", "zeta", "ban", "ab", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    std::cerr << "What is the string of the node you want to add? (to filledList): ";
    std::cin >> filledList;

    OrderedLinkedList emptyList{};
    filledList.printForwards();

    std::cout << "\n\n";

    std::cout << "What is the string of the node you want to add? (to emptyList): ";
    std::cin >> emptyList;

    std::cout << "Enter another (to emptyList): ";
    std::cin >> emptyList;
    emptyList.printForwards();

}

void plusEqualsListTest()
{
    
    std::cout << "Test of adding a filled list to a filled list \n";

    std::string arr1[4] = {"b", "c", "d", "e"}; 
    OrderedLinkedList filledList1{arr1, 4};
    
    std::string arr2[7] = { "aa", "ba", "ca", "cb", "cc", "ex", "ey" };  //Contains every iteration (adding to head, middle, consecutive middle, and end)
    OrderedLinkedList filledList2{arr2, 7};


    filledList1 += filledList2;
    filledList1.printForwards();
    
    
    std::cout << "\n\nTest of adding an empty list to itself (should print nothing)\n";
    OrderedLinkedList emptyList3{};
    emptyList3 += emptyList3;
    emptyList3.printForwards();

    


    std::cout << "\n\nTest of adding a filled list from the first operation to an empty list (should print same thing as first printout)\n";
    emptyList3 += filledList1;
    emptyList3.printForwards();

   

  
}

void equalsTest()
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};
    OrderedLinkedList equalList1{};
    equalList1 = filledList;
    std::cout << "Copied list of 6 elements:\n";
    equalList1.printForwards();
    std::cout << "\n\n";

    std::cout << "========================\ntest if the lists are pointing to separate nodes:\n";
    equalList1.modifyNode("ab", "aaaaaaaaaaaaabbbbbbb");
    std::cout << "List: \n";
    filledList.printForwards();

    std::cout << "\nCopy of List with 'ab' changed to aaaaaaaaaaaaabbbbbbb (should be different from previous list printout):\n"; //Shows that changing the copied linked list does not impact the original linked list
    equalList1.printForwards();
    std::cout << "\n========================\n";

    std::string oneArr[1] = {"zeta"}; 
    OrderedLinkedList oneEleList{oneArr, 1};
    OrderedLinkedList equalList2{};
    equalList2 = oneEleList;
    std::cout << "Copied list of 1 element:\n";
    equalList2.printForwards();
  
    std::cout << "\n\n";


    OrderedLinkedList nullList{};
    OrderedLinkedList equalList3{};
    std::cout << "Copied list of 0 elements:\n";
    equalList3 = nullList;
    equalList3.printForwards();
    std::cout << "\n\n";


    
}

void modifyNodeTest() //Only works if 1st parameter is actually found in the linked list
{
    std::string arr[6] = {"zeta", "ban", "ab", "test", "era", "lab"}; 
    OrderedLinkedList filledList{arr, 6};

    std::cout << "List with 'ab' changed to dog:\n";
    filledList.modifyNode("ab", "dog");
    filledList.printForwards();
    std::cout << "\n\n";

}
