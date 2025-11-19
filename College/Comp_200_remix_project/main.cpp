#include <iostream>
#include <iomanip>
#include <conio.h> // This makes our program only work on windows devices
using namespace std;
// Possibly make the maze system a separate class?
// UI elements below


void pickMood(string& face, int num)
{
    switch(num)
    {
        case 0: face = "(O u O)"; break;
        case 1: face = "(O - O)"; break;
        case 2: face = "(- . -)"; break;
    }
}

//void printUI(string face, string up, string down, string left, string right) // user sprite will be fixed
void movementUI(string face)
{
cout    << setw(23) <<  "level 2\n"  // Only used setw to make this more compact   
        << setw(22) << "w\n\n\n" 
        << "level 1 a" << setw(13) << face << setw(18) << "s level 3\n\n\n" 
        << setw(19) << "                  d" << '\n'
        << setw(22) << "               level 4";     
} 
void readInput(char& key)
{
    key = _getch();
}

int main()
{      
    string face;
    enum mood //bad practice to put this enum here but because this is a simple project it is fine. I did enum just for the sake of trying something new
    {
        HAPPY,
        NEUTRAL,
        SAD
    };
    
    char userInput = '\0';
    pickMood(face, mood(SAD));
    movementUI(face);
    while(userInput != 'w' && userInput != 'a' && userInput != 's' && userInput != 'd')
        readInput(userInput);
    
}


 
