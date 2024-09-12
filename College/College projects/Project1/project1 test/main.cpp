/*********************************************************************/
/* Author: Daniel Tripoli                                            */
/* Creation Date: September 6, 2024                                  */
/* Last Edited: September 11, 2024                                   */
/* Due Date: September 14th, 2024                                    */
/* Course: CPSC136 - Computer Science II                             */
/* Professor Name: Professor Wolfe                                   */
/* Assignment: Golf Swings                                           */
/* Filename: Project1.cpp                                            */
/* Purpose: Demonstrate knowledge of structs, functions, and sorting */
/*********************************************************************/

#include <fstream> //for I/O stream
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

//MAKE SURE TO MAKE OUTPUTS ALL HAVE 2 DECIMAL PLACES
//Need to program allowing sin( > 360 degrees)
struct swing //can you make constexpr structs
{
    std::string name;
    float angle;
    float initVelocity;
    double distance;
};

////////forward declarations///////////////////////////////////

/**
Name:           fillSwing
Description:    fills member variables of swing structs
Parameters:     string name - name of golfer,
                float velocity - initial velocity of golfer's swing, 
                float angle - the angle in degrees of the golfer's swing
Returns:        swing - a swing struct with a filled name, initial velocity, angle, and ball distance
**/

swing fillSwing(std::string name, float velocity, float angle);

/**
Name:           closeFile
Description:    closes file stream / access to the given file
Parameters:     ifstream extract - a file stream variable
Returns:        void
**/
void closeFile(std::ifstream& extract); //NOT CURRENTLY WORKING HUHRGEHRGERGERHRERUHgerhhgH

/**
Name:           openUserFile
Description:    open file stream / access to the given file, testing that the file exists
Parameters:     none
Returns:        ifstream - input file stream to extract data from said file
**/

std::ifstream openUserFile();
/**
Name:           swingFromUserFileToArray
Description:    Makes a sorted array of 10 structs max, with a separate function (selectionSort) organizing the structs by distance
Parameters:     swing arr[] - a list of struct swing (golfers)
Returns:        void
**/
void swingFromUserFileToArray(swing arr[]);

/**
Name:           selectionSort
Description:    Sorts the array of swing structs by distance, done by moving lesser distance swing structs left
Parameters:     swing arr[] - a list of swing structs (golfers)
Returns:        void
**/

void selectionSort(swing arr[], int sorted); //Need to make so it sorts every time I put swing var into arr

/**
Name:           swapSwingArray
Description:    Swaps locations of 2 swing structs in a swing array 
Parameters:     swing& left - the swing struct on the left side of the array 
                swing& right - the swing struct on the right side of the array 
Returns:        void
**/

void swapSwingArray(swing& left, swing& right);

/**
Name:           caclDist
Description:    Uses a projectile formula to find and return the distance of a swing struct, based on its member variables 
Parameters:     swing person - a golfer, used to access their values
Returns:        double - the distance of the golfer's hit
**/


double calcDist(swing person);

/**
Name:           returnCoterminal
Description:    Tests if golfer's hitting angle is within bounds (0 - 180 degrees),
                either finds the reference angle of the coterminal or changes distance
                to the other side if the angle is out of bounds
Parameters:     float angle - the angle of the golfer's hit
Returns:        float - either the same angle that came in or the new angle that fits angle rules
**/

float returnCoterminal(float angle);


/**
Name:           printCosmeticBorder
Description:    prints a cool looking border made out of "="!
Parameters:     none
Returns:        void
**/
void printCosmeticBorder();

/**
Name:           printSwingArr
Description:    prints out the array of swing structs, by printing each structs
                member variables with formatting to make it readable
Parameters:     swing arr[] - the array of swing structs
Returns:        void
**/

void printSwingArr(swing arr[]);

//////////////////main/////////////////////////////////////////



int main()
{
    system("CLS"); //for cosmetics, "clear" for unix, "CLS" for vscode

    swing arr[10]{};
    swingFromUserFileToArray(arr); //Creates array of swing structs organized by distance traveled
    printSwingArr(arr); //prints out swing arrays

}


/////////////////functions/////////////////////////////////////

swing fillSwing(std::string name, float velocity, float angle) //allows swing struct member vars to be filled
{
    swing person; //throwing warning of "synthesized method constexpr swing::swing required here"
    person.name = name;
    person.initVelocity = velocity;
    person.angle = angle;
    person.distance = calcDist(person);

    return person;
}

void closeFile(std::ifstream& extract) //NOT WORKING!
{
    extract.close();
}

std::ifstream openUserFile() //Opens an existing file if it exists
{
    std::string fileName;
    printCosmeticBorder();
    std::cout << "Enter a file name: ";
    std::cin >> fileName;
    std::ifstream extract{fileName};
    printCosmeticBorder();

    while(!extract) //Code to test file is real / not empty, as the end/nonexistence of a file outputs as 0
    {
        std::cerr << "File could not be found!\n Enter a new file name: ";
        std::cin >> fileName;
        printCosmeticBorder();
        extract.open(fileName);
    }

    return extract;
}

void swingFromUserFileToArray(swing arr[])
{
    std::ifstream extract{openUserFile()}; //takes 3 elements + tests for existing file
    float initVelocity;
    float angle;
    std::string name{};
    int i{0};

    while(extract >> name) //returns 0 at end, checks first val of row
    {
        if(i == 10) //checks if file is too big
            {
                std::cout << "=============================================\nThe file has exceeded the size of the array, stopping process at the 10th row...\n =============================================\n";
                break;
            }

        extract >> initVelocity;
        extract >> angle; 

        
        arr[i] = fillSwing(name, initVelocity, angle);
        ++i;
        selectionSort(arr, i);
    }

    closeFile(extract); //NOT WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //extract >> name;
    //std::cout << "NOT AN ERROR 1" << name;

    //extract.close();
    //extract >> name;
    //std::cout << "NOT AN ERROR 2" << name;
}

void selectionSort(swing arr[], int numElements) //Sorts swing structs in array arr by swing distances, from least to greatest
{
    int traverse{};

    for (int i{0}; i < numElements; i++) //still needs to stay just incase new value swaps old value to front
    {

        traverse = i;
    
        while( (arr[traverse].distance < arr[traverse - 1].distance) && (traverse > 0)) //Moves swing structs left while they are less than the value to the left of them, traverse cannot = 0 as it would lead to out of bounds
        {
            swapSwingArray(arr[traverse - 1], arr[traverse] );
            --traverse;  
        }

    }
}

void swapSwingArray(swing& left, swing& right) //& operator so we dont have to put in arr as a parameter
{
    swing placeholder{left};
    left = right;
    right = placeholder;
}

double calcDist(swing person) //calculates distance with the formula for a projectile
{
    constexpr double GRAVITY{9.81};
    return  ( ( (person.initVelocity * person.initVelocity) * std::sin( 2 * ( returnCoterminal(person.angle) * ( ( 2 * acos(0.0) ) / 180 ) ) ) / GRAVITY ) ); //Used inverse cos for finding pi, as cos is 0 at 90 degrees, so 90 * 2 = 180 degrees = pi
} 

float returnCoterminal(float angle) //Gives reference angle when the angle is above 360 or below 0 degrees. Also make distance positive from 270-360 degrees and negative from 180-270 degrees not inclusive  
{
    if (angle > 360) 
    {
        while (angle > 360)
            angle -= 360;
        return angle;
    }

    else if (angle < 0) //Don't really need 'else' because of the return but did it for readability
    {
        while (angle < 0)
            angle += 360;
        return angle;
    }

    else if ( (angle > 180) && (angle < 360) ) //makes it so downward left angles give negative dist, and lower right angles give positive
        return -angle;

    return angle;
}

void printCosmeticBorder()
{
    std::cout << "=============================================\n";
}

void printSwingArr(swing arr[])
{
   constexpr int dist{9}; //used to adjust text spacing quickly
    
   std::cout << std::setw(5) << "  Golfer Name" << std::setw(5) << "|" << std::setw(5) 
   << "    Initial Speed" << std::setw(5) << "|" << std::setw(5) << "    Launch Angle" 
   <<                        std::setw(5) << "|" << std::setw(5) << "    Distance" << '\n';

    for(int i{0}; i < 10; i++)
    {
        std::cout << std::setw(dist + 4) << arr[i].name << std::setw(dist - 4) << "|" << std::setw(dist + 4) 
        << std::fixed << std::setprecision(2) << arr[i].initVelocity << " m/s" << std::setw(dist - 4) << "|" << std::setw(dist + 6) //Used geekforgeek to learn about std::fixed of iomanip
        << arr[i].angle << '\370' <<  std::setw(dist - 4) << "|" << std::setw(dist + 1) << arr[i].distance << " m\n"; // \370 is the code for degree symbol, though this doesn't work in unix, only vscode
    
    }
        
}




 




