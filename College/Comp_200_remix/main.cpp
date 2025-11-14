#include <iostream>
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

 //void printUI(string face) // user sprite will be fixed
//{
        
//} 
int main()
{
    string face;
    enum mood //bad practice to put this enum here but because this is a simple project it is fine. I did enum just for the sake of trying something new
    {
        HAPPY,
        NEUTRAL,
        SAD
    };
    mood currentMood = HAPPY;
    pickMood(face, currentMood);
    cout << face;
    


    
}
