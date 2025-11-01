#include <string>
#include <iostream>
using namespace std;

// This implimentation is sort of improper, it only lets you build either a symmetric format of #--string--#+letter--string--#  ex: "613--fyh--5l--spo--231" or "613--fyh--5l--spo--231--alv"
// with the addition of extending by 1 char.
bool validateFormat(string input)
{ // Do note I consulted an ascii table online to assist in the implimentation (it wasn't specified if this was allowed)
    int size = int(input.size()); // The type conversion does nothing but make compilers happy (no warnings) as .size() is a double not int
    int hyphenCount{0}; // 0 entails the first section, keeps track of the amount of hyphens that have been passed
    bool expectHyphen{false}; //built only for unique case of the 1 letter and 1 letter after the 4th hyphen
    for(int i{0}; i < size; i++)
    {
        int asciiInt{input[i]};
        
        if(asciiInt == 45)
        { 
            hyphenCount++; // Case of hyphen
            if(expectHyphen == true)
            {
                expectHyphen = false;
            }

        }

        else if(expectHyphen == true) return false; // if the above if statement fails, then it implies the char is not a hyphen (important for the one sequence where hyphenCount == 4)
        else if(hyphenCount % 4 == 2) // Second segment, should be all letters. They are spread out by 4, but from an offset of 2, therefore hyphen % 2 = 2
        {  //checks for being in ascii range of letters (as this wasn't specified, but it could be simplified with string.tolower())
            if( !( (asciiInt >= 65 && asciiInt <= 90) || (asciiInt >= 97 && asciiInt <= 122) ) )
                return false;
        }
        else if(hyphenCount == 4) // third segment, int followed by letter. optimized by putting it below the letter segment case, which is present infinitely more in the proper format
        {
            if( !( (asciiInt >= 48 && asciiInt <= 57)  ) ) // first elem should be int
                return false;
            i++; // a workaround for having to check to strings
            asciiInt = input[i];
            // I could make the below a checkIfLetter() function but due to the small scale of this task, this works!
            if( !( (asciiInt >= 65 && asciiInt <= 90) || (asciiInt >= 97 && asciiInt <= 122) ) ) //second elem should be letter
                return false;
            expectHyphen = true;
        }
        else if(hyphenCount % 8 == 0) // First segment should be all #'s
        {
            if( !( (asciiInt >= 48 && asciiInt <= 57)  ) )
                return false;
        }
        else return false; // rules out case of impropper hyphens (there must be an even amount)
        
    }
    return true;
} 

int main()
{
    cout << validateFormat("613--fyh--5l--spo--231--alv");
}
