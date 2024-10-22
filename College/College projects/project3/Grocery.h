/**********************************************************************/
/*    Author:           Professor Bohdan D. Jacklitsch                */
/*    Creation Date:    September 19, 2024                            */
/*    Last Edited:      September 19, 2024                            */
/*    Course:           CPSC136 - Computer Science II                 */
/*    Filename:         Grocery.h                                     */
/*    Purpose:          Header of Grocery class                       */
/**********************************************************************/

#ifndef GROCERY_H
#define GROCERY_H

using namespace std;

// This class serves to act as an entry at a store's inventory system. It contains a grocery's name, the amount
//   in inventory, and where it is located in terms of department, and when relevant, aisle number. It handles
//   conversion of any strings to uniformly formatted ones for ease of organization, and provides opposing
//   comparison operator overloads to allow easy comparison in multiple ways.
class Grocery
{
    public:
    
        /**
           Name:        Constructor
           Description: The basic, empty constructor, to be used for placeholding
           Parameters:  None
           Returns:     None
        **/
        Grocery();
        
    
        /**
           Name:        Constructor
           Description: Constructor with 1 required argument and 3 optional ones
                          utilizing default parameters
           Parameters:  string groceryName (input) - The initializing value of the object's groceryName
                        int inventoryCount (input) - The initializing value of the object's inventoryCount, 1 by default
                        string groceryDepartment (input) - The string used to determine the groceryDepartmentID, empty by default
                        int aisleNumber (input) - The initializing value of the object's aisleNumber, -1 by default
           Returns:     None
        **/
        Grocery(string groceryName, int inventoryCount = 1, string groceryDepartment = "", int aisleNumber = -1);
        
        /**
           Name:        Copy Constructor
           Description: The basic copy constructor, which does a standard copy
           Parameters:  const Grocery& referenceGrocery (input) - The Grocery to copy from
           Returns:     None
        **/
        Grocery(const Grocery& referenceGrocery);
        
        /**
           Name:        Destructor
           Description: The basic destructor, which destroys the object as expected
           Parameters:  None
           Returns:     None
        **/
        ~Grocery();
        
        /**
           Name:        getGroceryName
           Description: Getter for groceryName
           Parameters:  None
           Returns:     string - The value of the object's groceryName
        **/
        string getGroceryName();
        
        /**
           Name:        setGroceryName
           Description: Setter for groceryName
           Parameters:  string groceryName (input) - The value which the object's groceryName will be set to
           Returns:     None
        **/
        void setGroceryName(string groceryName);
        
        /**
           Name:        getInventoryCount
           Description: Getter for inventoryCount
           Parameters:  None
           Returns:     int - The value of the object's inventoryCount
        **/
        int getInventoryCount();
        
        /**
           Name:        setInventoryCount
           Description: Setter for inventoryCount
           Parameters:  int inventoryCount (input) - The value which the object's inventoryCount will be set to
           Returns:     None
        **/
        void setInventoryCount(int inventoryCount);
        
        /**
           Name:        getGroceryDepartment
           Description: Transformative Getter for groceryDepartmentID
           Parameters:  None
           Returns:     string - The value of the object's groceryDepartmentID, stringified
        **/
        string getGroceryDepartment();
        
        /**
           Name:        setGroceryDepartment
           Description: Transformative Setter for groceryDepartmentID
           Parameters:  string groceryDepartment (input) - The string which be interpreted to set the object's groceryDepartmentID
           Returns:     None
        **/
        void setGroceryDepartment(string groceryDepartment);
        
        /**
           Name:        getAisleNumber
           Description: Getter for aisleNumber
           Parameters:  None
           Returns:     int - The value of the object's aisleNumber
        **/
        int getAisleNumber();
        
        /**
           Name:        setAisleNumber
           Description: Setter for aisleNumber
           Parameters:  int aisleNumber (input) - The value which the object's aisleNumber will be set to
           Returns:     None
        **/
        void setAisleNumber(int aisleNumber);
        
        /**
           Name:        isAisleDepartment
           Description: Returns whether the grocery is in an aisle or not
           Parameters:  None
           Returns:     bool - True if the departmentID is aisle, False otherwise
        **/
        bool isAisleDepartment() const;  //IS THIS OK I MADE IT CONST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        /**
           Name:        isUnsortedDepartment
           Description: Returns whether the grocery is in a department or not
           Parameters:  None
           Returns:     bool - True if the departmentID is unsorted, False otherwise
        **/
        bool isUnsortedDepartment();
        
        /**
           Name:        > Operator Overload
           Description: Checks if left Grocery is in a higher location than the right Grocery,
                          based on enum ordering and aisle number when relevant
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to compare to
           Returns:     bool - True if the object is in a "higher" department/isle, False otherwise
        **/
        bool operator>(const Grocery& rightGrocery);
        
        /**
           Name:        >= Operator Overload
           Description: Checks if left Grocery is in the same or a higher location than the right Grocery,
                          based on enum ordering and aisle number when relevant
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to compare to
           Returns:     bool - True if the object is in the same or "higher" location, False otherwise
        **/
        bool operator>=(const Grocery& rightGrocery);
        
        /**
           Name:        < Operator Overload
           Description: Checks if left Grocery is alphabetically smaller than the right Grocery, based on
                          their groceryName values
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to compare to
           Returns:     bool - True if the object's name is alphabetically smaller, False otherwise
        **/
        bool operator<(const Grocery& rightGrocery);
        
        /**
           Name:        < Operator Overload
           Description: Checks if left Grocery is alphabetically smaller than or equal to the right Grocery, based on
                          their groceryName values
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to compare to
           Returns:     bool - True if the object's name is alphabetically the same or smaller, False otherwise
        **/
        bool operator<=(const Grocery& rightGrocery);
        
        /**
           Name:        == Operator Overload
           Description: Checks if the two Grocery objects have the same groceryName
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to compare to
           Returns:     bool - True if both Grocerys have the same name, False otherwise
        **/
        bool operator==(const Grocery& rightGrocery);
        
        /**
           Name:        += Operator Overload
           Description: Adds rightGrocery's inventoryCount to this object and changes this object's department/aisle
                          number to be the same as rightGrocery's, unless rightGrocery is unsorted.
           Parameters:  const Grocery& rightGrocery (input) - The Grocery to use to alter this one
           Returns:     Grocery& - Reference to this Grocery object for chaining
        **/
        Grocery& operator+=(const Grocery& rightGrocery);
        
        /**
           Name:        << Operator Overload
           Description: Prints out details (data members) of a Grocery item, each detail on a seperate line
           Parameters:  ostream& os (output) - The output stream used to print the Grocery details
                        const Grocery& printingGrocery (input) - The Grocery to print from
           Returns:     ostream& - Reference to the used ostream for chaining
        **/
        friend ostream& operator<<(ostream& os, const Grocery& printingGrocery);

    private:
        // Enum privately used by the class to store ids and sort and such
        enum departmentID {deli, bakery, produce, meat, aisles, dairy, frozen, unsorted};
        
        /**
           Name:        reformatStringCapitalization
           Description: Reformats a string to be capitalized in a consistant way, where each word
                          has its first letter capitalized
           Parameters:  string& passedString (input/output) - The string to reformat
           Returns:     None
        **/
        void reformatStringCapitalization(string& passedString);
        
        /**
           Name:        stringToDepartmentID
           Description: Gets the int value of the passed string's associated departmentID
           Parameters:  string groceryDepartment (input) - The string to turn into an associated departmentID
           Returns:     int - The integer cooresponding to the departmentID's enum value
           Notes:       It SHOULD be returning a departmentID instead, but it is causing trouble.
                          as such, functions which use this will need to typecast back to a departmentID
        **/
       int stringToDepartmentID(string groceryDepartment) const;

        
        /**
           Name:        departmentIDToString
           Description: Gets the passed groceryDepartmentID's associated string
           Parameters:  departmentID groceryDepartmentID (input) - The departmentID to turn into an associated string
           Returns:     string - The string representing an associated departmentID
           Notes:       See, it doesn't wine when it's a parameter. Bah.
        **/
        string departmentIDToString(departmentID groceryDepartmentID) const;
    
        // The name of a product
        string groceryName;
        // The amound of them in inventory
        int inventoryCount;
        // The departmentID of the grocery
        departmentID groceryDepartmentID;
        // What aisle it is in; only matters if groceryDepartmentID is aisles
        int aisleNumber;
};

#endif
