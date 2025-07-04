#include <string>
#include <iostream>
using namespace std;
string convertToTitle(int columnNumber) 
{
    string ans{""};
    while(columnNumber > 0)
    {
        columnNumber--; //This was trial and error, I saw my anwer was one off (I.E. I got "B" when I should've gotten "A"), likely because we start at 'A', not the char before, so we need to cancel this out
        ans = char(columnNumber % 26 + 'A') + ans; //Chars are very similar to the excel system, but since the number system is different from chars,
                                                   // we add the char value for 'A' to bring it up to the start of the alphabet for chars
        columnNumber = columnNumber / 26; //Once we are done a digit, we remove the value we "translated" to excel already
    }
    return ans;
}

int main()
{
    cout << convertToTitle(701);
}
