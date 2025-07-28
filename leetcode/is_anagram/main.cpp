#include <string>
#include <map>
#include <iostream>
using namespace std;

//Slowish approach with maps! The fastest way would be to sort the string and then compare each index, but that would just be using a library function (and making the function by hand is unproductive)
bool isAnagram(string s, string t) 
{
    if(s.size() != t.size())
        return false;
    //char is letter, int is count of that letter
    map<char, int> letterS;
    map<char, int> letterT;
    for(char letter : s)
        letterS[letter]++;
    for(char letter : t)
        letterT[letter]++;
    auto itS = letterS.begin();
    auto itT = letterT.begin();
    while(itS != letterS.end())
    {
        if( (itS -> first != itT -> first) || (itS -> second != itT -> second) )
            return false;
        itS++;
        itT++;
    }
    return true;
}

int main()
{
    cout << isAnagram("rat", "car");
}
