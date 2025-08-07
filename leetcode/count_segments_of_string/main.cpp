#include <string>
#include <iostream>
using namespace std;
int countSegments(string s) 
{
    int segCount;
    if(s.size() == 0) //edge case of empty string
        return 0;
    if(s[0] == ' ') //Case of starting with a space (or many of them)
        segCount = 0;
    else //Case of starting with a segment
        segCount = 1;
    
    for(int i{0}; i < (s.size() - 1); i++)
        if(s[i] == ' ' && s[i + 1] != ' ')
            segCount++;
    return segCount;
}
int main()
{
    cout << countSegments("     apple pie") << '\n'; //2
    cout << countSegments(" b     s  apA5#21 ") << '\n'; //3
}
