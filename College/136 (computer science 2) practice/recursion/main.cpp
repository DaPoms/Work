/**************************************************************************************************
   Author:          Bohdan D. Jacklitsch
   Creation Date:   9/30/2024
   Last Modified:   11/8/2024
   Course:          CPSC135 060
   Filename:        project2Functified.cpp
   Purpose:         This program is used to see how far items shot
					  directly into the air reach and how long it
					  took to get to that maximum height; it does
                      all this using functions.
**************************************************************************************************/

#include <iostream>

using namespace std;

/*
    Name:         determineFibonacci
    Description:  Determines the fibonacci number at the given location using recursion
    Parameters:   int fibonacciLocation - Which fibonacci number is being calculated 
    Returns:      int - That fibonacci number, or -1 on failure
*/
long determineFibonacci(int fibonacciLocation);

int main()
{
    int fibonacciLocation;
    long nthFibonacci;
    cout << "Which fibonacci number do you want? ";
    cin >> fibonacciLocation;
    
    nthFibonacci = determineFibonacci(fibonacciLocation);
    cout << "The " << fibonacciLocation << "th fibonacci number is " << nthFibonacci << endl;
    
    return 0;
}

long determineFibonacci(int fibonacciLocation)
{
    if (fibonacciLocation <= 2)
    {
        if (fibonacciLocation == 2)
        {
            return 1;
        }
        else if (fibonacciLocation == 1)
        {
            return 0;
        }
        return -1;
    }
    
    return (determineFibonacci(fibonacciLocation-1) +
			determineFibonacci(fibonacciLocation-2));
}
