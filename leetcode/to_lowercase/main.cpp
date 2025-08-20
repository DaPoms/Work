#include <iostream>
#include <string> //Lesson learned! not all compilers accept iostream for basic string support, so from now on I'm including it just in case
using namespace std;
//This was the easiest leetcode I've done so far!
string toLowerCase(string s) 
{
    for(char& letter : s)
    {
        if(int(letter) <= 90 && int(letter) >= 65)
            letter += 32;
    }
    return s;
}
int main()
{
    cout << toLowerCase("HELLO WORLD!");
}
