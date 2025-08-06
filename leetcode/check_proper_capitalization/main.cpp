#include <iostream>
#include <string>
using namespace std;
bool detectCapitalUse(string word) {
    int capitalCount{0};
    for(int charToInt : word)
        if(charToInt >= 41 && charToInt <= 90)
            capitalCount++;
    
    if(capitalCount == 0 || capitalCount == word.size())
        return true;
    else if(capitalCount == 1)
    {
        if(word[0] >= 41 && word[0] <= 90)
            return true;
        else
            return false;
    }
    else
        return false;
}

int main()
{
    cout << detectCapitalUse("APPL") << '\n'; //True
    cout << detectCapitalUse("APPl") << '\n'; //False
    cout << detectCapitalUse("appl") << '\n'; //True
    cout << detectCapitalUse("regRWSEgreee") << '\n'; //False
}
