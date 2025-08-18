#include <iostream>
using namespace std;
    bool judgeCircle(string moves) 
    {
        pair<int,int> coords{0,0};//first is x, second is y
        for(char command : moves)
        {
            switch(command) //This implimentation taught me about the "fall through" behavior of switch cases, where unless you have a break in each case, everything below the case which "command" is valid for will also be run
            {
                //I also learned this unique format for when you're doing one thing in each case, it's only readable in cases where similar actions are being done for each case
                case 'L': coords.first++;
                    break;
                case 'R': coords.first--;
                    break;
                case 'U': coords.second++;
                    break;
                case 'D': coords.second--;
                    break;
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
