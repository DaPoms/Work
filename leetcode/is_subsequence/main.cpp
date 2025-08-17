#include <string>
#include <iostream>
using namespace std;

//Approach 2 (better approach): Traverse s's chars in t, if s doesn't reach the end, it means s is not a subsequence of t as some char is blocking it's traversal
bool isSubsequence(string s, string t)
{
    int sIndex{0};
    for(char tletter : t)
    {
        if(s[sIndex] == tletter)
            sIndex++;
    }
    if(sIndex == s.size())
        return true;
     return false;
}

//Approach one: manipulating string t to == string s
/* 
    bool isSubsequence(string s, string t) 
    {
        int sIndex{0};
        int tIndex{0};
        while(tIndex < t.size() && t.size() >= s.size())
        {
            if(s[sIndex] != t[tIndex])
            {
                t.erase(tIndex, 1);
                tIndex--; //erasing makes us have to go backwards to make sure we don't skip over a value on the next tIndex++
            }
            else
                sIndex++;
            tIndex++;
        }
        if(s.size() == t.size())
            return true;
        else
            return false;
    }
 */
int main()
{
    cout << isSubsequence("axc", "ahbgdc");
}
