#include <iostream>
//Testing how to watch array while in a function 

/*
parameter arr[] (An array) is passed as a reference, which is why debuggers don't 
detect the inputted parameter while debugging, as its actually the reference/memory 
location that is being watched. The fix for this is to directly call the variable in the watch tab,
which in this example would be "arr, 20" . The number is the size of the array
*/

void incrementArray(int arr[], int numElements) 
{
    int incrementer{0};

    for(int i{0}; i < numElements; i++)
    {
        arr[i] = incrementer;
        ++incrementer;
    }
}


int main()
{
    int arr[20];
    incrementArray(arr, 20);
}
