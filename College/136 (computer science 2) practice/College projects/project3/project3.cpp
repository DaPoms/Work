/**********************************************************************/
/*    Author:           Daniel Tripoli                                */
/*    Creation Date:    October 20, 2024                              */
/*    Last Edited:      October 21, 2024                              */
/*    Course:           CPSC136 - Computer Science II                 */
/*    Filename:         Project3.cpp                                  */
/*    Purpose:          Get a grade (and demonstrate knowledge in my  */
/*                      opinion of creating class function forward    */
/*                      declarations and comments)                    */
/**********************************************************************/

#include <iostream>
#include "Grocery.h"
#include <fstream>
#include <sstream>
#include <iomanip>

///////forward declares

/**
    Name:        printBorder
    Description: prints out a row of "=" to act as a border for the terminal.
    Parameters:  None
    Returns:     None
**/
void printBorder();

/**
    Name:        waitForUser
    Description: prints text for user to continue, and will continue the program when user presses enter
    Parameters:  None
    Returns:     None
**/

void waitForUser();

/**
    Name:        mainMenuUserInput
    Description: prints menu UI and takes input for main menu navigation
    Parameters:  char& passedChar - variable that will store user's input in the main menu in the scope of wherever the function was called
    Returns:     None
**/

void mainMenuUserInput(std::string& passedChar);

/**
    Name:        fileToInventory
    Description: extracts Groceries from .txt files and puts them in array passedInventory[]
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void fileToInventory(Grocery passedInventory[], int& numElements); 

/**
    Name:        fileNameIndex
    Description: Searches for the inputted Grocery inside a list of Groceries
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
                 std::string userGroceryName - the inputted name to be searched for in the list, passedInventory

    Returns:     int - index where the Grocery was found in the list, or -1 if it was not found
**/

int findNameIndex(Grocery passedInventory[], int& numElements, std::string userGroceryName);

/**
    Name:        fileNameIndex
    Description: Asks for a name to find then searches for the given Grocery name inside a list of Groceries
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     int - index where the Grocery was found in the list, or -1 if it was not found
**/

int findNameIndex(Grocery passedInventory[], int& numElements);

/**
    Name:        printGrocery
    Description: prints member variables of class Grocery in a list of Groceries, testing that it fits within inventory bounds of 100  
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int passedIndex - index of inventory that is going to be printed
                 bool wait - waits for user to press enter if true, ends immediately otherwise.
    Returns:     None
**/

void printGrocery(Grocery passedInventory[], int passedIndex, bool wait);

/**
    Name:        userAddGrocery
    Description: Asks user for input to create a Grocery and then puts it into the passedInventory list, combining duplicates
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void userAddGrocery(Grocery passedInventory[], int& numElements);


/**
    Name:        addGrocery
    Description: Adds a passed Grocery object to the passedInventory list of Groceries
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
                 Grocery addedGrocery - whatever Grocery that is to be added to passedInventory
    Returns:     None
**/

void addGrocery(Grocery passedInventory[], int& numElements, Grocery addedGrocery);

/**
    Name:        readFileLineToGrocery
    Description: Uses a getline to read one line of text from a .txt file and assigns it to a grocery variable.
    Parameters:  ifstream& extract - extracts text from the .txt file
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     Grocery - contains assigned values from a line of a .txt file
**/

Grocery readFileLineToGrocery(ifstream& extract, int& numElements);

/**
    Name:        printDepartmentOrder
    Description: Sorts the given list of Groceries by their value of the enum departmentID from least to greatest, then prints it out in table form
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void printDepartmentOrder(Grocery passedInventory[], int& numElements);

/**
    Name:        printAlphabetOrder
    Description: Sorts the given list of Groceries by alphabetical order by Grocery names, then prints it out in table form
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void printAlphabetOrder(Grocery passedInventory[], int& numElements);

/**
    Name:        printInventory
    Description: prints out all Groceries in a list/inventory in a table format
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void printInventory(Grocery passedInventory[], int& numElements);

/**
    Name:        changeDepartment
    Description: Allows user to change department of existing Grocery in a list/inventory,
                 asking for an aisle # if the users inputs "aisle" and asking the user for a new Grocery to look for if their previous Grocery was not found in the list
    Parameters:  Grocery passedInventory[] - A list which stores Groceries
                 int& numElements - number of Groceries in the passedInventory array
    Returns:     None
**/

void changeDepartment(Grocery passedInventory[], int& numElements);

/////////Const variables////////////////

const int ARRAY_CAPACITY{100}; //Made global const so it works in functions

///////////New fixes:///////////////
/*

No array capacity constant; instead, "100" was hardcoded throughout - Fixed
Menu does not inform user of faulty input in main menu - Fixed
Menu uses while loop with no initialization of menuInput beforehand, causing potential immediate cessation - Fixed (declared to "NULL")
Does not use << operator overload to print detailed Grocery data - Already on line 538
Does not close file after processing - fixed on 359
Always passes the same number of arguments to the constructor when reading from file rather than using default parameters
Prints aisle # for other departments, not just for groceries in aisles - fixed with using isDepartmentIsle

*/
///////////////////////////////////////

int main()
{


    printBorder();
    system("cls");

   
    int numElements = 0;
    std::string menuInput{"NULL"}; //Takes user input for the menus NOTE!!!!: Changed to a string so that the program doesn't take an input like "mmmmmc" as being char 'c' at the end of the set of chars, and instead interprets it as a misinput
     Grocery inventory[ARRAY_CAPACITY]; //Array of 100 grocery products   

   
	while( (menuInput != "Q") && (menuInput != "q") )
    {
      mainMenuUserInput(menuInput);

        if ( (menuInput == "F") || (menuInput == "f") )
            printGrocery( inventory, findNameIndex(inventory, numElements), 1);  
        
        else if ( (menuInput == "A") || (menuInput == "a") )
            userAddGrocery(inventory, numElements);

        else if ( (menuInput == "R") || (menuInput == "r") )
            fileToInventory(inventory, numElements);
            
        else if ( (menuInput == "C") || (menuInput == "c") )
            changeDepartment(inventory, numElements);

        else if ( (menuInput == "N") || (menuInput == "n") )
            printAlphabetOrder(inventory, numElements);

        else if ( (menuInput == "D") || (menuInput == "d") )
            printDepartmentOrder(inventory, numElements);

        else if (menuInput != "Q" && menuInput != "q")
        {
            std::cout << "Wrong input! Press enter to try again...\n"; //Note i
            waitForUser();
        }

    }

}

void printInventory(Grocery passedInventory[], int& numElements) 
{
    std::cout << "=====================================================================================\n";
    int dist{8};
    std::cout <<  std::setw(dist + 3) << "Name" << std::setw(dist) << "|" << std::setw(dist + 4) << "Count" << std::setw(dist) << "|" << std::setw(dist + 9) << "Department" << std::setw(dist) << "|" << std::setw(dist + 12) << "Aisle Number\n";
    std::cout << "=====================================================================================\n";
    for(int i{0}; i < numElements; i++)                                            
    {
        std::cout << std::setw(dist + 3) << passedInventory[i].getGroceryName() << std::setw(dist) << "|" << std::setw(dist + 4) << passedInventory[i].getInventoryCount() << std::setw(dist) << "|" << std::setw(dist + 9) << passedInventory[i].getGroceryDepartment() << std::setw(dist) << "|" << std::setw(dist + 12); 
       
        if(passedInventory[i].isAisleDepartment() < 1) //TEST THAT THIS WORKS
        {
            std::cout << '\n';
        }

        else
        {
            std::cout<< passedInventory[i].getAisleNumber() << '\n';
        }
    }

}

void printAlphabetOrder(Grocery passedInventory[], int& numElements)
{
    system("cls");

    for(int i{1}; i < numElements; i++) 
    {

        for(int sort{1}; sort < numElements; sort++)
        {
           if(passedInventory[sort] < passedInventory[sort - 1]) 
            {
                Grocery placeholder = passedInventory[sort - 1];
                passedInventory[sort - 1] = passedInventory[sort];
                passedInventory[sort] = placeholder;
            }
        
        }
    }

  

    printInventory(passedInventory, numElements);
    std::cout << "=====================================================================================\n";
    waitForUser();
}

void printDepartmentOrder(Grocery passedInventory[], int& numElements)
{
    system("cls");

    for(int i{1}; i < numElements; i++) //testing value ahead, so numElements - 1 prevents going out of array
    {

      //  int traverse = i;

        for(int sort{1}; sort < numElements; sort++)
        {
           if(passedInventory[sort - 1] > passedInventory[sort]) 
            {
                Grocery placeholder = passedInventory[sort - 1];
                passedInventory[sort - 1] = passedInventory[sort];
                passedInventory[sort] = placeholder;
            }
        
        }
    }

    printInventory(passedInventory, numElements);
    std::cout << "=====================================================================================\n";
    waitForUser();
}

void printBorder()
{
    std::cout << "======================================================\n";
}

void waitForUser()
{
    std::cout << "Press enter to continue...";
    std::string wait;
    std::getline(std::cin, wait); //Enter from previous inputs get put in here, so this is to reset that
    std::getline(std::cin, wait);
}

void mainMenuUserInput(std::string& passedChar) //Used reference to prevent instantiating the same variable multiple times
{
    system("cls"); //Need to let it work so 
    printBorder();

    std::cout << "F - Find and print out the details of a provided grocery\n" <<
                 "A - Add a grocery\n" <<
                 "R - Read and insert groceries from a properly formatted file\n" <<
                 "C - Change a grocery's department\n" <<
                 "N - Print out all the grocery information in alphabetical order\n" << //Make it so it works with capitals and lowercase
                 "D - Print out all the grocery information by department order\n" << 
                 "Q - Quit application\n";

    printBorder();

    std::cin >> passedChar;
 
}

void fileToInventory(Grocery passedInventory[], int& numElements)
{
    system("cls"); //
    std::string fileName;
    std::cout << "Enter your file name: ";
    std::cin >> fileName;
    Grocery endCheck;

    std::ifstream extract{fileName};

    while (!extract) //If user enters a file that doesn't exist / empty
    {
        std::cout << "Your file does not exist or is empty! Enter a new file: ";
        std::cin >> fileName;
        extract.open(fileName);
    }

    

    while(extract) 
    {
        endCheck = readFileLineToGrocery(extract, numElements); 
        if( !(endCheck.getGroceryName() == "") ) //Made it so it ignores cases where user forgets to include name / leaves a blank line, also fixes my bug I had on the 100th term if list had 99 items
            addGrocery( passedInventory, numElements, endCheck ); 
    }
    
    printBorder();
    std::cout << "Items added or combined to inventory.\n";
    printBorder();
    waitForUser();

    extract.close(); //New fix, actually closes stream now
}

Grocery readFileLineToGrocery(ifstream& extract, int& numElements) //When count is empty it does memory value, need to fix
{
    std::string inputLine;
    std::string name;
    int count{1}; //1 is default if no count is present
    std::string countTest;
    std::string department;
    int aisleNum{};

    std::getline(extract, inputLine); //fills line of file to string inputLine
    std::istringstream lineReader(inputLine); //creates a stream just for 1 line
    
    lineReader >> name >> count >> department; 
    
   // Grocery extractedGrocery{name, count, department}; //Only fix would be to do default param and then setFunct count and department if they arent whitespace
    Grocery extractedGrocery{name};
    if(count != 0) 
    {
        extractedGrocery.setInventoryCount(count);

        if(department != "") //Only tests department if count is given, as a count of 0 means the object doesn't exist, so you may as well not assign department
            extractedGrocery.setGroceryDepartment(department);
    }

    if( extractedGrocery.isAisleDepartment() )
    {
        lineReader >> aisleNum;
        extractedGrocery.setAisleNumber(aisleNum);
    }
    
    

    return extractedGrocery;
}

void changeDepartment(Grocery passedInventory[], int& numElements)
{
    

    std::string departmentInput;
    std::string groceryNameInput;
    int aisleNum;
    int i{-1};

    while (i <= -1)
    {
        system("cls");
        printBorder();
        std::cout << "Whats the name of the grocery you want to change the department of?\nOR type 'exit' to quit\n\n";
        std::cin >> groceryNameInput;
        std::cout << '\n';
        printBorder();

        i = findNameIndex(passedInventory, numElements, groceryNameInput);
       
        if( (groceryNameInput == "exit") || (groceryNameInput == "Exit") ) //Exits when user types "exit"
            return;

        else if(i == -1) //Needed to be below exit if statement so that it doesn't print this when user could care less if "exit" is a grocery or not
        {
            

            std::cout << groceryNameInput << " could not be found in the Inventory.\n";
            printBorder();
           
            system("read -p \"Click enter to try again...\n\" ");
        }
        
    }

    printGrocery(passedInventory, i, 0);
    printBorder();

    std::cout << "What department do you want to change " << passedInventory[i].getGroceryName() << " to?: ";
    std::cin >> departmentInput;

    passedInventory[i].setGroceryDepartment(departmentInput);

    if(passedInventory[i].isAisleDepartment()) //Do I HAVE to use isAisleDepartment()? comparing the string is more efficient
    {
        std::cout << "What aisle is " << passedInventory[i].getGroceryName() << " in?: ";
        std::cin >> aisleNum;
        passedInventory[i].setAisleNumber(aisleNum);
    }

    printBorder();
    std::cout << "Changed Grocery:\n";
    printBorder();
    printGrocery(passedInventory, i, 0); //Shows end result after department change
    printBorder();
    waitForUser();
}

int findNameIndex(Grocery passedInventory[], int& numElements, std::string userGroceryName) //tries to find given name parameter in name member of Grocery objects in passInventory
{ 
    for (int i = 0; i < numElements; i++) 
    {
        if (passedInventory[i] == userGroceryName) ///TEST THIS
        return i;
    } 
         
    return -1; //failure code    
}

void printGrocery(Grocery passedInventory[], int passedIndex, bool wait) //prints grocery of given index from list
{
    if ( (passedIndex >= 0) && (passedIndex  < ARRAY_CAPACITY)) //this is so code runs only if value exists
        std::cout << passedInventory[passedIndex];

    if(wait == 1)
    {
        printBorder();
        waitForUser();
    }
}

int findNameIndex(Grocery passedInventory[], int& numElements) //Asks for user to enter grocer name
{
    system("cls");
    printBorder();

    std::cout << "What grocery do you want to find?: ";
    std::string userGroceryName;
    std::cin >> userGroceryName; 
 
    for (int i = 0; i < numElements; i++) //test NUMELEMENTS WITH 100, 101, and 99 items!!!
        {
            if (passedInventory[i] == userGroceryName) 
                return i;
        } 
         
        std::cout << userGroceryName << " is not in the inventory!\n\n";
        return -1; //failure code    
}



void userAddGrocery(Grocery passedInventory[], int& numElements) //Only fails when user inputs wrong data (string in int)
{
    system("cls");
    printBorder();


    std::string name;
    int count;
    std::string department; 
    int aisleNum;


    std::cout << "Enter the grocery's name: ";
    std::cin >> name;

    std::cout << "Enter the count of " << name << ": ";
    std::cin >> count;

    std::cout << "Enter the department for " << name << ": ";
    std::cin >> department;

    Grocery addedGrocery{name, count, department}; //Fun fact: Before you fixed the class constructor not capitalizing departmentID input, I used a set function for departmentID to capitalize
   


    if(addedGrocery.isAisleDepartment()) //Asks for aisle number if user's department is an isle
    {
        std::cout << "Enter the aisle of " << name << ": ";
        std::cin >> aisleNum;
        addedGrocery.setAisleNumber(aisleNum);
    }

    int index; //location of pre-existing Grocery in the inventory
    printBorder();

    if( ( (index = findNameIndex(passedInventory, numElements, name) ) >= 0)) //if grocery in array
    {
        passedInventory[index] += addedGrocery; //adds count of entered Grocery to pre-existing object
        system("cls");
        printBorder();
        std::cout << name << " combined to pre-existing " << name << " in inventory!\n";

        printBorder();
        std::cout << passedInventory[index]; ///HEREFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        printBorder();
        waitForUser();

    }

    else if (numElements >= ARRAY_CAPACITY) //Tests if inventory is full
    {
        std::cout << "The inventory is full! Unable to add " << name << " to inventory.\n";
        printBorder();
        waitForUser();
        return;
    }
  
    else
    {
        passedInventory[numElements] = addedGrocery;

        ++numElements;

        system("cls");
        printBorder();
        std::cout << name << " added to inventory!\n";
        printBorder();
        
        std::cout << addedGrocery; 
        printBorder();
        waitForUser();
    }
}

void addGrocery(Grocery passedInventory[], int& numElements, Grocery addedGrocery) //Uses default values when .txt is formatted incorrectly, this version of the function has no cout so it can be used for processes
{
    int index;

    if( ( (index = findNameIndex(passedInventory, numElements, addedGrocery.getGroceryName() ) ) >= 0)) //if grocery in array
    {
        passedInventory[index] += addedGrocery; //adds count to pre-existing item
    }

    else if (numElements >= ARRAY_CAPACITY)
    {
        std::cout << "\nThe inventory is full! Unable to add " << addedGrocery.getGroceryName() << " to inventory.\n";
        return;
    }
    
    else //New groceries added to inventory here
    {
        passedInventory[numElements] = addedGrocery;
        ++numElements;
    }
}

