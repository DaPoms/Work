#include <iostream>
#include <string>
using namespace std;

//This is such a convoluted method to solving this problem, but it was fun doing it this way. I like doing this to show how a different perspective (such as the 2nd approach below) can make a problem much simpler
bool checkLayout(string s, string goal, int start) //Checks if the starting point for string 's' makes shifted properly to be equal to string 'goal'. If it is, then it's our answer for this problem
{
    int goalIndex{0};
    int endIndex{static_cast<int>(s.size())}; //Starting value stays s.size() only when string s and goal both start with the same letter
    if(start != 0)
        endIndex = start - 1; //case where we need to loop around for string s (most cases)
        
    for(int i{start}; i != endIndex && goalIndex < s.size(); i++)
    {
        if(s[i] != goal[goalIndex])
            return false;
        if(i != 0 && (i % (s.size() - 1)) == 0 ) //circular traversal implimentation 
            i = -1;
        goalIndex++;
    }
    if(s[endIndex] == goal[goalIndex])
        return true;
    return false;
}
bool rotateString(string s, string goal) 
{
        if(s.size() != goal.size())
            return false;

        int i{0}; //i is the index in string 's' that string 'goal' starts at
        bool isCorrect{false};
        while(!isCorrect && i < s.size())
        {
            if(s[i] == goal[0])
                isCorrect = checkLayout(s,goal,i);
            i++;
        }
        if(isCorrect == false)
            return false;
        return true;
}

//this implimentation is one I found from another user, it works rather simply: if we can find the goal string in a chain of s strings, then it is a rotation of string s
/* 
bool rotateString(string s, string goal)
{
    if(s.size() != goal.size()) return false; //Covers the one edge case : different sized strings
    string chain = s + s;
    if(chain.find(goal) <= chain.size()) return true; //Statement is true if find returns any index within chain's size
    return false;
}
 */
int main()
{                        
    cout << rotateString("abcde", "abcde");
}
