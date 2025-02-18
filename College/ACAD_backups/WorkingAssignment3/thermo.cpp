/************************************************************/
/* Author: Daniel Tripoli                                   */
/* Major: Computer Science                                  */
/* Creation Date: February 7th, 2025                        */
/* Due Date: February 14, 2025                              */
/* Course: CSC237 010                                       */
/* Professor Name: Dr.Hussain                               */
/* Assignment: #3                                           */
/* Filename: Counter.cpp                                     */
/* Purpose: Simulate a Thermostat managing heating and AC   */
/************************************************************/

/*	Compile statement:

	To compile: g++ thermo.cpp

*/

#include <iostream>
#include <unistd.h>
using namespace std;
//#include "thermoCounter.h"
#include "counter.h"

//Forward declares here



/*
    Function name:   getTemp 
    Description:     asks for the user to give their current room temperature
    Parameters:      none 
    Return Value:    int - the int the user inputs
*/
int getTemp();

/*
    Function name:   
    Description:     
    Parameters:     
    Return Value:   
*/
void turnOnAC(Counter currTemp, int setpoint);

/*
    Function name:   
    Description:     
    Parameters:     
    Return Value:   
*/
void turnOnHeat(Counter currTemp, int setpoint);

/*
    Function name:   
    Description:     
    Parameters:     
    Return Value:   
*/
int getTemp()
{
    cout << "Enter your current temperature (must be from 50-80): "; //Do we need to repeat ask if they are outside bound?
    int userTemp{};

    cin >> userTemp;

    while(userTemp < 50 || userTemp > 80)
    {
        cout << "Invalid value! (value must be between 50-80)\n";
        cin >> userTemp;
    }
    
    return userTemp;

}

void turnOnAC(Counter currTemp, int setpoint)
{
    cout << "AC turned on.\n";

    while(currTemp.get_value() > setpoint)
    {
        sleep(2);
        currTemp.decrement(2);
        cout << "Room temperature:  " << currTemp.get_value() << '\n';
    }

    cout << "AC turned off.";
}


void turnOnHeat(Counter currTemp, int setpoint)
{
    cout << "Heater turned on.\n";

    while(currTemp.get_value() < setpoint)
    {
        sleep(2);
        currTemp.increment(2);
        cout << "Room temperature:  " << currTemp.get_value() << '\n';
    }

    cout << "Heater turned off.\n";
}


/*	Write Comments Here	*/
int main()
{
    int setPoint{70}, currTemp{}; // Change this var to set temp point
    currTemp = getTemp(); 
    Counter userTemp{currTemp};  

    if(currTemp < setPoint) 
       turnOnHeat(userTemp, setPoint);
    else if(currTemp > setPoint)
        turnOnAC(userTemp, setPoint);
    else
        cout << "Room temperature is already at the set point!\n";

    return EXIT_SUCCESS;
}

