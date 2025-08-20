#include <iostream>
using namespace std;
    bool judgeCircle(string moves) 
    {
        pair<int,int> coords{0,0};//first is x, second is y
        for(char command : moves)
        {
            switch(command) //This implimentation taught me about the "fall through" behavior of switch cases, where unless you have a break in each case, everything below the case which "command" is valid for will also be run
            {
                // Heres another even more compact format with brackets. 
                //I now understand what people mean by how you can make "one line" programs! (although anything past this amount on one line is unnecessarily unreadable)
                case 'L': coords.first++; break;
                case 'R': coords.first--; break;
                case 'U': coords.second++; break;
                case 'D': coords.second--; break;
            }
        }
        if(coords.first == 0 && coords.second == 0)
            return true;
        return false;
    }

int main()
{
    cout << judgeCircle("DU");
}
