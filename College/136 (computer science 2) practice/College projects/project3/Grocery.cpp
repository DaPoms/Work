#include <iostream>
#include "Grocery.h"

Grocery::Grocery() //empty constructor
{
    groceryName = "";
    inventoryCount = 0;
    groceryDepartmentID = unsorted; //7 is enum for unsorted
    aisleNumber = -1;
}

Grocery::Grocery(std::string groceryName, int inventoryCount, std::string groceryDepartment, int aisleNumber) //default parameters can only be defined in EITHER header or .cpp, but not both
{
   reformatStringCapitalization(groceryName);
   (*this).groceryName = groceryName;
   (*this).inventoryCount = inventoryCount;
   reformatStringCapitalization(groceryDepartment); //Need to make sure user input is capitalized for 1st letter
   (*this).groceryDepartmentID = (departmentID)stringToDepartmentID(groceryDepartment); //need to convert string to enum riujeghniguoerghwuerghowehbweregbiwwergbu
   (*this).aisleNumber = aisleNumber;
}

Grocery::~Grocery() //Deconstructor
{}

Grocery::Grocery(const Grocery& referenceGrocery) //Copy constructor
{
    groceryName = referenceGrocery.groceryName;
    inventoryCount = referenceGrocery.inventoryCount;
    groceryDepartmentID = referenceGrocery.groceryDepartmentID;
    aisleNumber = referenceGrocery.aisleNumber;
}

std::string Grocery::getGroceryName() //Returns grocery object's name
{
    return groceryName; //Don't need to capitalize because the set + constructor functions both capitalize - which are the only ways to input the groceryName
}

void Grocery::setGroceryName(std::string groceryName) //Changes grocery object's name to given parameter
{
    reformatStringCapitalization(groceryName);
    (*this).groceryName = groceryName;
}


int Grocery::getInventoryCount() //Returns grocery object's inventory count
{
    return (*this).inventoryCount;
}
        
void Grocery::setInventoryCount(int inventoryCount) //Changes grocery object's inventory count to given parameter
{
    (*this).inventoryCount = inventoryCount;
}

std::string Grocery::getGroceryDepartment() //Returns grocery object's department 
{
    return departmentIDToString(groceryDepartmentID);
}

void Grocery::setGroceryDepartment(std::string groceryDepartment) //Changes grocery object's department to given parameter
{
    reformatStringCapitalization(groceryDepartment);
    groceryDepartmentID = (departmentID)stringToDepartmentID(groceryDepartment); 
}

int Grocery::getAisleNumber() //Returns grocery object's aisle number
{
    return aisleNumber; 
}

void Grocery::setAisleNumber(int aisleNumber) //Changes grocery object's aisle number to given parameter
{
    (*this).aisleNumber = aisleNumber;
}

bool Grocery::isAisleDepartment() const //Tests if grocery object's department is an aisle. Made it const because anything output in here does not need to be changed
{
    if(groceryDepartmentID == aisles)
        return true;

    return false;
}

bool Grocery::isUnsortedDepartment() //returns true is enum groceryDepartmentID is the value: unsorted
{  
    if(groceryDepartmentID == unsorted)
        return true;

    return false;
}

bool Grocery::operator>(const Grocery& rightGrocery) //Checks if left Grocery is a higher location than the right Grocery, based on enum ordering and aisle number when relevant
{
    if( ( (*this).isAisleDepartment() == 1 ) && ( rightGrocery.isAisleDepartment() == 1 ) ) //Did this because its fun, but I had to make isAisleDepartment const in order to let me use the function inside of this operator overload
        if((*this).aisleNumber > rightGrocery.aisleNumber)
            return true;
        else
            return false; //Added else for readability, not necessary (just return false is fine)

        
    if((*this).groceryDepartmentID > rightGrocery.groceryDepartmentID) //Could also call the funct to turn ID into int and then compare ints
        return true;

    return false; 

}
        
   
bool Grocery::operator>=(const Grocery& rightGrocery) //Checks if left Grocery is in the same or a higher location than the right Grocery, based on enum ordering and aisle number when relevant
{
    if( ( (*this).isAisleDepartment() == 1 ) && ( rightGrocery.isAisleDepartment() == 1 ) ) //Did this because its fun, but I had to make isAisleDepartment const in order to let me use the function inside of this operator overload
        if((*this).aisleNumber > rightGrocery.aisleNumber || (*this).aisleNumber == rightGrocery.aisleNumber)
            return true;
        else
            return false; //Added else for readability, not necessary (just return false is fine)

        
    if((*this).groceryDepartmentID > rightGrocery.groceryDepartmentID || (*this).groceryDepartmentID == rightGrocery.groceryDepartmentID) //Could also call the funct to turn ID into int and then compare ints
        return true;

    return false; 
}       

    
bool Grocery::operator<(const Grocery& rightGrocery) //Checks if left Grocery is alphabetically smaller than the right Grocery, based on their groceryName values
{
    if((*this).groceryName < rightGrocery.groceryName) //This is fine because all names are automatically capitalized
        return true;
    else //Once again for cosmetics
        return false;
}


bool Grocery::operator<=(const Grocery& rightGrocery) //Checks if left Grocery is alphabetically smaller than or equal to the right Grocery, based on their groceryName values
{
    if((*this).groceryName < rightGrocery.groceryName || (*this).groceryName == rightGrocery.groceryName ) //This is fine because all names are automatically capitalized
        return true;
    else //Once again for cosmetics
        return false;
}


bool Grocery::operator==(const Grocery& rightGrocery) //Checks if the two Grocery objects have the same groceryName
{
    if( (*this).groceryName == rightGrocery.groceryName)
        return true;
        
    else
        return false;
}



Grocery& Grocery::operator+=(const Grocery& rightGrocery) //Adds count to left grocery object and replaces the aisle number
{
    (*this).inventoryCount += rightGrocery.inventoryCount; //Adds count

    if(rightGrocery.groceryDepartmentID != unsorted)
    {
        (*this).groceryDepartmentID = rightGrocery.groceryDepartmentID;

        //if (rightGrocery.isAisleDepartment() == true) You could add an isAisleDepartment if statement here, but my project3.cpp accounts for aisle input anyways by not allowing the user to add an aisle number unless department is aisles. If you did want this for grading reasons, well here is the code just commented out
        (*this).aisleNumber = rightGrocery.aisleNumber;        
    }
    return (*this); 
}


std::ostream& operator<<(ostream& os, const Grocery& printingGrocery) //Outputs member variables of grocery objects in a SUPER COOL FORMAT! Only prints Aisle number when the department is aisles
{

    std::cout << "Grocery:" << "      " << printingGrocery.groceryName << "\n"; //I gave up on setw because it gets angry when words are too long
    std::cout << "In Inventory:" << " " << printingGrocery.inventoryCount << "\n"; 
    if(printingGrocery.isAisleDepartment() == true)
            {
                std::cout << "Aisle Number:" << " " << printingGrocery.aisleNumber << "\n"; 
                return os;
            }
    std::cout << "Department:" << "   " << printingGrocery.departmentIDToString(printingGrocery.groceryDepartmentID) << "\n"; //We don't print department if the groceryDepartment is aisle so this is just fine!
    return os;
}




void Grocery::reformatStringCapitalization(string& passedString) //Used whenever a string is called to follow the rule that "Every string must be capitalized, capitalizing the first letter in every word"
{ 
    if(passedString[0] != ' ')
        passedString[0] = toupper(passedString[0]); //Decided to test independently the first val as my for loop is made to test if string starts with a space, but does not account for the 1st value of the string

   for(int traverseLetter{1}; traverseLetter < passedString.length(); traverseLetter++) //check through every letter in the string (including spaces and symbols)
   {
        if( (passedString[traverseLetter - 1] == ' ') && (passedString[traverseLetter] != ' ') ) //Justlearned about stringVar[number] from this, doing stringVar[number] makes a char, not a 1 letter string 
            passedString[traverseLetter] = toupper(passedString[traverseLetter]);
        else
            passedString[traverseLetter] = tolower(passedString[traverseLetter]); //A little inefficient but assignment doesn't hurt much
   }
}


int Grocery::stringToDepartmentID(string groceryDepartment) const //converts string to departmentID enum
{
    if (groceryDepartment == "Deli")
        return 0;

    else if (groceryDepartment == "Bakery")
        return 1;

    else if (groceryDepartment == "Produce")
        return 2;

    else if (groceryDepartment == "Meat")
        return 3;

    else if (groceryDepartment == "Aisles" || groceryDepartment == "Aisle")
        return 4;

    else if (groceryDepartment == "Dairy")
        return 5;

    else if (groceryDepartment == "Frozen")
        return 6;

    return 7; //Unsorted case, we don't need to check for "Unknown" if we just add it at the end!
    

}


string Grocery::departmentIDToString(departmentID groceryDepartmentID) const //Returns enum member variable departmentID of a grocery object in its string representation
{
    switch (groceryDepartmentID)
    {
        case deli:
            return "Deli";

        case bakery:
            return "Bakery";

        case produce:
            return "Produce";

        case meat:
            return "Meat";

        case aisles:
            return "Aisles"; 

        case dairy:
            return "Dairy";

        case frozen:
            return "Frozen";
    }

    return "Unknown"; //Case of unsorted, seems like you made it print "unknown", so I matched it
}
