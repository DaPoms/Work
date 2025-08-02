#include <map>
#include <iostream>
#include <string>
using namespace std;
char findTheDifference(string s, string t) 
{
    map<char, int> lettersS; // We keep track of how much there is of each string's characters, then compare the longer t string to the shorter S string to ultimately find the difference
    map<char, int> lettersT;
    for(char letter : s)
        lettersS[letter]++;
    for(char letter : t)
        lettersT[letter]++;

    auto itS = lettersS.begin();
    auto itT = lettersT.begin();
    while(itT != lettersT.end())
    {
        if((itS -> first != itT -> first) || (itS -> second != itT -> second)) //The second parameter checking the count is for the case that an already used letter is the extra char for string t
            return itT -> first;
        itT++;
        itS++;
    }
    return '\0'; //error case (string t should always be 1 char off of string s)
}

int main()
{
    cout << findTheDifference("aaa", "aaza") << '\n'; //returns z
    cout << findTheDifference("", "o") << '\n'; //should return o
    cout << findTheDifference("aaa", "aaaa"); //Should return a
}
