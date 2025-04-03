//This is my messy first approach to a recursive string flipping, I'm still trying to understand the best way to create recursive functions, particularly with having variables that we want to add onto


#include <iostream>
#include <string>
using namespace std;
void recursivePrintInvertString(string& passedString, int size, int index = 0) //This program only prints the inverse, it doesn't create the object currently
{
    char myChar = passedString[index];
    if(index != size - 1)
        recursivePrintInvertString(passedString, size, ++index);
    cout << myChar;

}

string stringInvert(string& passedString, string& invertedString, int size, int index = 0) 
//This function unlike the other one, actually 
//outputs a string with the flipped result. I decided not to do that inside of the recursion because its extremely inefficient to assign for each recurison step,
// so instead I made a helper function
{
    char myChar = passedString[index];
    if(index != size - 1)
        stringInvert(passedString, invertedString, size, ++index);
    invertedString += myChar;
    return invertedString;
}

/* 
helper function that allows us to more efficiently assign our output to the passed string. If we did this in a class,
the function that actually does the recursion (the one above) would be private whearas this function would be public, as the user doesn' need access to this
 */
void recursiveInvertString(string& passedString, string& invertedString, int size, int index = 0) 
{
    passedString = stringInvert(passedString, invertedString, size, index);
}

int main()
{
    string myString{"They call me STEVE. As a child, I yearned for the mines."}; //This example shows how horrible my algorithm is! (it takes a while to run) Though I do know recursion is often very slow
    string invertedString{""};
    recursivePrintInvertString(myString, 56);
    cout << '\n';
    recursiveInvertString(myString, invertedString, 56);
    cout << myString;
}
